#include "../SymmetricMinMaxHeapCppLib/SymmetricMinMaxHeapCppLib.h"

#include <tchar.h>

#ifdef _DEBUG
	#pragma comment(lib, "../Debug/SymmetricMinMaxHeapCppLib.lib")
#else
	#pragma comment(lib, "../Release/SymmetricMinMaxHeapCppLib.lib")
#endif

void ViewArray(SymmetricMinMaxHeap* heap)
{
	_tprintf(_T("[ "));
	for (unsigned int i = 0; i < heap->TakeSize() + 2; i++)
	{
		_tprintf(_T("%d"), heap->TakeArray()[i]);
		if (i != (heap->TakeSize() + 1))
			_tprintf(_T(", "));
	}
	_tprintf(_T(" ]\n"));
}

void PrintSample(DATATYPE* sources)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_tprintf(_T("%2d "), sources[(i * 8) + j]);
		}
		_tprintf(_T("\n"));
	}
}


int CompareFunc(DATATYPE* left, DATATYPE* right)
{
	if ((*left) < (*right))
		return -1;
	else if ((*left) > (*right))
		return 1;
	else
		return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	SymmetricMinMaxHeap* Heap = new SymmetricMinMaxHeap(CompareFunc, 4);
	SymmetricMinMaxHeap* AscHeap = new SymmetricMinMaxHeap(CompareFunc, 4);
	SymmetricMinMaxHeap* DscHeap = new SymmetricMinMaxHeap(CompareFunc, 4);

	DATATYPE sources[64] = { 6, 4, 46, 11, 10, 45, 13, 24,
							48, 20, 35, 62, 64, 37, 50, 22,
							25, 27, 36, 44, 38, 39, 17, 5,
							19, 51, 2, 7, 52, 30, 58, 33,
							1, 49, 29, 18, 42, 55, 53, 60,
							57, 40, 3, 15, 21, 54, 14, 61,
							59, 8, 12, 16, 56, 34, 32, 63,
							41, 28, 26, 47, 23, 43, 31, 9 };

	DATATYPE AscSorted[64] = { 0, };
	DATATYPE DscSorted[64] = { 0, };

	_tprintf(_T("\n##### 64-Digit Random Sequence #####\n"));

	PrintSample(sources);

	_tprintf(_T("\nBefore Insert : "));
	ViewArray(Heap);

	for (unsigned int i = 0; i < 64; i++)
	{
		Heap->Insert(sources[i]);
		AscHeap->Insert(sources[i]);
		DscHeap->Insert(sources[i]);
	}

	_tprintf(_T(" After Insert : "));
	ViewArray(Heap);
	_tprintf(_T(" After Clear  : "));
	Heap->Clear();
	ViewArray(Heap);

	_tprintf(_T("\n##### Sort using SymmetricMinMaxHeap #####\n"));

	for (unsigned int i = 0; i < 64; i++)
	{
		AscSorted[i] = AscHeap->TakeMin();
		AscHeap->DeleteMin();
		DscSorted[i] = DscHeap->TakeMax();
		DscHeap->DeleteMax();
	}

	_tprintf(_T("----- Ascending -----\n"));
	PrintSample(AscSorted);
	_tprintf(_T("----- Decending -----\n"));
	PrintSample(DscSorted);

	return 0;
}