#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdint.h>

namespace GEC
{

	/*
		Linear allocator returns memory for use from a pre-allocated buffer. It does not called dtors and must
		be manually cleared once EVERYTHING in the allocator is safe to dispose of.

		Is not natively thread safe but could easily be made so by using thread locals

		Once alignof is more widely adopted we should default to aligned allocations

		TODO:
			Needs to be configured/configurable to use jemalloc
	*/
	class LinearAllocator
	{
	public:
		explicit LinearAllocator(size_t space):mTotalSpace(space)
		{
			mStart = new uint8_t[space];
			mCur = mStart;
		}

		~LinearAllocator()
		{
			delete[] mStart;
			mStart = nullptr;
			mCur = mStart;
			mTotalSpace = 0;
		}

		size_t GetTotalSpace()const { return mTotalSpace; }
		size_t GetSpaceUsed()const { return mCur-mStart; }
		size_t GetSpaceRemaining()const{ return GetTotalSpace() - GetSpaceUsed(); }

		void* RequestSpace(size_t bytes)
		{
			void* retval = nullptr;

			if (bytes < GetSpaceRemaining())
			{
				retval = mCur;
				mCur += bytes;
			}

			return retval;
		}

		//use of perfect forwarding to allow new with params
		// see http://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/
		template<typename T, typename ...Args>
		T* New(Args&&... args)
		{
			void* res = RequestSpace(sizeof(T));
			if (res == nullptr)
				return nullptr;

			return new(res)T(std::forward<Args>(args)...);
		}

		//Does NOT call any dtors
		void Clear()
		{
			mCur = mStart;
		}

	private:
		uint8_t	* mStart = nullptr, 
				* mCur = nullptr;
		size_t mTotalSpace = 0;

	private:
		LinearAllocator(const LinearAllocator&copy) = delete;
	};
}

#endif//LINEAR_ALLOCATOR_H