#ifndef __SYMMETRIC_MIN_MAX_HEAP_CPP_LIB__
#define __SYMMETRIC_MIN_MAX_HEAP_CPP_LIB__

#ifdef __cplusplus

#include <stdlib.h>
#include <cstring>

extern "C"
{
#endif

#ifdef _COMPLING_DLL_
	#define LIBSPEC __declspec(dllexport)
#else
	#define LIBSPEC __declspec(dllimport)
#endif
	typedef int DATATYPE;

	class LIBSPEC SymmetricMinMaxHeap
	{
	private:
		unsigned int _Size;
		unsigned int _ArraySize;
		unsigned int _InitialSize;

		DATATYPE* L;

		int(*compar)(DATATYPE* LeftValue, DATATYPE* RightValue);

		void Swap(unsigned int indexA, unsigned int indexB);
		void Resize(unsigned int size);
		void Expand();
		
		static unsigned int uLnode(unsigned int index);
		static unsigned int uRnode(unsigned int index);
	public:
		SymmetricMinMaxHeap::SymmetricMinMaxHeap(int(*compar)(DATATYPE* LeftValue, DATATYPE* RightValue), unsigned int InitialSize);
		~SymmetricMinMaxHeap();

		void Insert(DATATYPE value);
		int TakeMin();
		int TakeMax();
		void DeleteMin();
		void DeleteMax();
		void Clear();
		unsigned int TakeSize();

		DATATYPE* TakeArray();
	};


#ifdef __cplusplus
}
#endif

#endif