#include "MyArray.h"

template <typename _T>
void MyArray<_T>::resize(int newlen)
{
	if (newlen == length)
		return;
	if (newlen < length)
	{
		_T* temp = new _T[newlen];
		memcpy(temp, data, sizeof(_T) * newlen);
		delete[] data;
		data = temp;
	}

	else if (newlen > length)
	{
		_T* temp = new _T[newlen];
		memcpy(temp, data, sizeof(_T) * length);
		delete[] data;
		data = temp;
	}

	length = newlen;
}

template class MyArray<int>;
template class MyArray<float>;
