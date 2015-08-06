#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdint.h>

namespace GEC
{

	/*
		Linear allocator returns memory for use from a pre-allocated buffer. It does not called dtors and must
		be manually cleared once EVERYTHING in the allocator is safe to dispose of.

		Is not natively thread safe but could easily be made so by using thread locals
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