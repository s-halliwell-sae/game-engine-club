#ifndef JEM_STL_ALLOC
#define JEM_STL_ALLOC

#include "jemalloc/jemalloc.h"
#include <allocators>

/**
	Provides jemalloc based versions of stl allocators, POD version doesn't call ctor dtor

	Once alignof becomes common place, we should default to using aligned_alloc with alignof<T>
*/

namespace GEC
{
	template <class T>
	struct JemAllocator {
		typedef T value_type;
		JemAllocator(/*ctor args*/){ je_init(); }
		//template <class T> JemAllocator(const JemAllocator<T>& other);
		T* allocate(std::size_t n)
		{
			return (T*)je_malloc(n);
		}
		void deallocate(T* p, std::size_t n)
		{
			je_free(p);
		}
	};


	//pods don't use ctors or dtors
	template <class T>
	struct JemAllocatorPOD {
		typedef T value_type;
		JemAllocatorPOD(/*ctor args*/){ je_init(); }
		//template <class T> JemAllocator(const JemAllocator<T>& other);
		T* allocate(std::size_t n)
		{
			return (T*)je_malloc(n);
		}
		void deallocate(T* p, std::size_t n)
		{
			je_free(p);
		}

		//pods don't use ctors or dtors
		template <class U, class... Args>
		void construct(U* , Args&&... )
		{
		}

		template <class U>
		void destroy(U* )
		{
		}
	};
}

template <class T, class U>
bool operator==(const GEC::JemAllocator<T>&, const GEC::JemAllocator<U>&)
{
	return false;
}
template <class T, class U>
bool operator!=(const GEC::JemAllocator<T>&, const GEC::JemAllocator<U>&)
{
	return true;
}

template <class T>
bool operator==(const GEC::JemAllocator<T>&, const GEC::JemAllocator<T>&)
{
	return true;
}
template <class T>
bool operator!=(const GEC::JemAllocator<T>&, const GEC::JemAllocator<T>&)
{
	return false;
}

template <class T, class U>
bool operator==(const GEC::JemAllocatorPOD<T>&, const GEC::JemAllocatorPOD<U>&)
{
	return false;
}
template <class T, class U>
bool operator!=(const GEC::JemAllocatorPOD<T>&, const GEC::JemAllocatorPOD<U>&)
{
	return true;
}

template <class T>
bool operator==(const GEC::JemAllocatorPOD<T>&, const GEC::JemAllocatorPOD<T>&)
{
	return true;
}
template <class T>
bool operator!=(const GEC::JemAllocatorPOD<T>&, const GEC::JemAllocatorPOD<T>&)
{
	return false;
}


#endif//JEM_STL_ALLOC