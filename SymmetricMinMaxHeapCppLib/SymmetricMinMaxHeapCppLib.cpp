#define _COMPLING_DLL_

#include "SymmetricMinMaxHeapCppLib.h"

/*
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

static int uLnode(unsigned int index);
static int uRnode(unsigned int index);
public:
SymmetricMinMaxHeap(int(*compar)(DATATYPE* LeftValue, DATATYPE* RightValue), unsigned int InitialSize = 4);
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

*/

SymmetricMinMaxHeap::SymmetricMinMaxHeap(int(*compar)(DATATYPE* LeftValue, DATATYPE* RightValue), unsigned int InitialSize)
{
	this->_Size = 2;

	if (InitialSize < 4)
		this->_ArraySize = 4;
	else
		this->_ArraySize = InitialSize;

	this->L = (DATATYPE*)malloc(sizeof(DATATYPE) * this->_ArraySize);//new DATATYPE[this->_ArraySize];
	memset(this->L, 0, sizeof(DATATYPE) * this->_ArraySize);

	this->_InitialSize = InitialSize;

	this->compar = compar;
}

SymmetricMinMaxHeap::~SymmetricMinMaxHeap()
{
	if (this->L != NULL)
		delete[] this->L;
}


void SymmetricMinMaxHeap::Swap(unsigned int indexA, unsigned int indexB)
{
	DATATYPE temp = this->L[indexA];
	this->L[indexA] = this->L[indexB];
	this->L[indexB] = temp;
}

void SymmetricMinMaxHeap::Resize(unsigned int size)
{
	unsigned int CurrentSize = this->_ArraySize;
	if (size > CurrentSize)
	{
		this->L = (DATATYPE*)realloc(this->L, sizeof(DATATYPE) * size);
	}
}

void SymmetricMinMaxHeap::Expand()
{
	this->Resize(this->_ArraySize * 2);
	this->_ArraySize *= 2;
}

unsigned int SymmetricMinMaxHeap::uLnode(unsigned int index)
{
	unsigned int temp = (index / 4) * 2;
	if (temp == 0)
		return 0;
	else
		return temp;
}

unsigned int SymmetricMinMaxHeap::uRnode(unsigned int index)
{
	unsigned int temp = (index / 4) * 2;
	if (temp == 0)
		return 0;
	else
		return temp + 1;
}


void SymmetricMinMaxHeap::Insert(DATATYPE value)
{
	this->L[this->_Size] = value;
	unsigned int _CurrentIndex = this->_Size;
	this->_Size++;
	if ((_CurrentIndex % 2) == 1)
	{
		if (this->L[_CurrentIndex - 1] > this->L[_CurrentIndex])
		{
			this->Swap(_CurrentIndex - 1, _CurrentIndex);
			_CurrentIndex--;
		}
	}

	unsigned int _lnode = 0, _rnode = 0;
	while (true)
	{
		_lnode = SymmetricMinMaxHeap::uLnode(_CurrentIndex);
		_rnode = SymmetricMinMaxHeap::uRnode(_CurrentIndex);
		if ((_lnode != 0) && ((*this->compar)(&(this->L[_CurrentIndex]), &(this->L[_lnode])) == -1))
		{
			this->Swap(_CurrentIndex, _lnode);
			_CurrentIndex = _lnode;
		}
		else if ((_lnode != 0) && ((*this->compar)(&(this->L[_CurrentIndex]), &(this->L[_rnode])) == 1))
		{
			this->Swap(_CurrentIndex, _rnode);
			_CurrentIndex = _rnode;
		}
		else
		{
			break;
		}
	}

	if (this->_Size >= this->_ArraySize)
		this->Expand();
}
DATATYPE SymmetricMinMaxHeap::TakeMin()
{
	if (this->_Size > 2)
	{
		return this->L[2];
	}
	else
		return NULL;
}

DATATYPE SymmetricMinMaxHeap::TakeMax()
{
	if (this->_Size > 3)
	{
		return this->L[3];
	}
	else if (this->_Size == 3)
	{
		return this->L[2];
	}
	else
		return NULL;
}


void SymmetricMinMaxHeap::DeleteMin()
{
	this->_Size--;
	this->L[2] = this->L[this->_Size];
	unsigned int _CurrentIndex = 2;

	unsigned int _lnode = 0, _rnode = 0;
	while (true)
	{
		_lnode = _CurrentIndex * 2;
		_rnode = (_CurrentIndex * 2) + 2;

		if (_rnode < this->_Size)
		{
			if ((*this->compar)(&(this->L[_lnode]), &(this->L[_rnode])) == -1)
			{
				if ((*this->compar)(&(this->L[_lnode]), &(this->L[_CurrentIndex])) == -1)
				{
					if ((*this->compar)(&(this->L[_lnode]), &(this->L[_lnode + 1])) == 1)
					{
						this->Swap(_lnode + 1, _CurrentIndex);
						_CurrentIndex = (_lnode + 1);
					}
					else
					{
						this->Swap(_lnode, _CurrentIndex);
						_CurrentIndex = _lnode;
					}
				}
				else
					break;

			}
			else if ((*this->compar)(&(this->L[_lnode]), &(this->L[_rnode])) != -1)
			{
				if ((*this->compar)(&(this->L[_rnode]), &(this->L[_CurrentIndex])) == -1)
				{

					if ((_rnode + 1) < this->_Size)
					{
						if ((*this->compar)(&(this->L[_rnode]), &(this->L[_rnode + 1])) == 1)
						{
							this->Swap(_rnode + 1, _CurrentIndex);
							_CurrentIndex = (_rnode + 1);
							continue;
						}
					}

					this->Swap(_rnode, _CurrentIndex);
					_CurrentIndex = _rnode;
				}
				else
					break;
			}
		}
		else if (_lnode < this->_Size)
		{
			if ((*this->compar)(&(this->L[_lnode]), &(this->L[_CurrentIndex])) == -1)
			{
				if ((_lnode + 1) < this->_Size)
				{
					if ((*this->compar)(&(this->L[_lnode]), &(this->L[_lnode + 1])) == 1)
					{
						this->Swap(_lnode + 1, _CurrentIndex);
						_CurrentIndex = (_lnode + 1);
						continue;
					}
				}

				this->Swap(_lnode, _CurrentIndex);
				_CurrentIndex = _lnode;
			}
			else
				break;
		}
		else
		{
			if ((_CurrentIndex + 1) < this->_Size)
			{
				if ((*this->compar)(&(this->L[_CurrentIndex]), &(this->L[_CurrentIndex + 1])) == 1)
					this->Swap(_CurrentIndex, _CurrentIndex + 1);
			}
			break;
		}
	}
}

void SymmetricMinMaxHeap::DeleteMax()
{
	this->_Size--;
	this->L[3] = this->L[this->_Size];
	unsigned int _CurrentIndex = 3;

	unsigned int _lnode = 0, _rnode = 0;
	while (true)
	{
		_lnode = (_CurrentIndex * 2) - 1;
		_rnode = (_CurrentIndex * 2) + 1;

		if (_rnode < this->_Size)
		{
			if ((*this->compar)(&(this->L[_lnode]), &(this->L[_rnode])) == 1)
			{
				if ((*this->compar)(&(this->L[_lnode]), &(this->L[_CurrentIndex])) == 1)
				{
					if ((*this->compar)(&(this->L[_lnode]), &(this->L[_lnode + 1])) == -1)
					{
						this->Swap(_lnode + 1, _CurrentIndex);
						_CurrentIndex = (_lnode + 1);
					}
					else
					{
						this->Swap(_lnode, _CurrentIndex);
						_CurrentIndex = _lnode;
					}
				}
				else
					break;

			}
			else if ((*this->compar)(&(this->L[_lnode]), &(this->L[_rnode])) != 1)
			{
				if ((*this->compar)(&(this->L[_rnode]), &(this->L[_CurrentIndex])) == 1)
				{

					if ((_rnode + 1) < this->_Size)
					{
						if ((*this->compar)(&(this->L[_rnode]), &(this->L[_rnode + 1])) == -1)
						{
							this->Swap(_rnode + 1, _CurrentIndex);
							_CurrentIndex = (_rnode + 1);
							continue;
						}
					}

					this->Swap(_rnode, _CurrentIndex);
					_CurrentIndex = _rnode;
				}
				else
					break;
			}
		}
		else if (_lnode < this->_Size)
		{
			if ((*this->compar)(&(this->L[_lnode]), &(this->L[_CurrentIndex])) == 1)
			{
				if ((_lnode + 1) < this->_Size)
				{
					if ((*this->compar)(&(this->L[_lnode]), &(this->L[_lnode + 1])) == -1)
					{
						this->Swap(_lnode + 1, _CurrentIndex);
						_CurrentIndex = (_lnode + 1);
						continue;
					}
				}

				this->Swap(_lnode, _CurrentIndex);
				_CurrentIndex = _lnode;
			}
			else
				break;
		}
		else
		{
			if ((_CurrentIndex + 1) < this->_Size)
			{
				if ((*this->compar)(&(this->L[_CurrentIndex]), &(this->L[_CurrentIndex + 1])) == -1)
					this->Swap(_CurrentIndex, _CurrentIndex + 1);
			}
			break;
		}
	}
}

void SymmetricMinMaxHeap::Clear()
{
	this->_Size = 2;
	this->_ArraySize = this->_InitialSize;
	this->L = (DATATYPE*)malloc(sizeof(DATATYPE) * this->_ArraySize);
}

unsigned int SymmetricMinMaxHeap::TakeSize()
{
	return this->_Size - 2;
}

DATATYPE* SymmetricMinMaxHeap::TakeArray()
{
	return this->L;
}