#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename _T>
class MyArray
{
public:
	MyArray(string name = "", int length = 0, bool initialize = false, _T val = 0)
	{
		init(name, length, initialize, val);
	}

	void init(string name = "", int length = 0, bool initialize = false, _T val = 0)
	{
		this->name = name;
		if (length > 0)
		{
			this->length = length;
			if (data != nullptr)
			{
				delete[] data;
				data = 0;
			}

			data = new _T[length]; //

			if (initialize)
			{
				for (size_t i = 0; i < length; i++)
					data[i] = val;
			}
		}
		else
		{
			this->length = 0;
			if (data != nullptr)
			{
				delete[] data;
				data = 0;
			}
		}
	}

	int size() const
	{
		return length;
	}

	void resize(int newlen);
	void print()
	{
		cout << "array " << name << " contains: \n";
		for (size_t i = 0; i < length-1; i++)
			cout << data[i] << ", ";

		cout << data[length-1] << "\n";
	}

	/*int get(int idx)
	{
		return data[idx];
	}*/
	//سربارگذاری عملگر اندیس
	_T& operator[](int idx)
	{
		if (idx >= 0 && idx < length)
			return data[idx];
		else
			throw out_of_range("invalid index");
	}

	MyArray& operator+= (int val)
	{
		for (size_t i = 0; i < length; i++)
		{
			data[i] += val;
		}

		return *this;
	}

	MyArray& operator+= (MyArray& b)
	{
		if (length != b.length)
			throw invalid_argument("array b must have the same dimension as input array");
		for (size_t i = 0; i < length; i++)
		{
			data[i] += b[i];
		}

		return *this;
	}

	/*MyArray* operator+ (MyArray& b)
	{
		int j = 0;
		if (length != b.length)
			throw invalid_argument("array b must have the same dimension as input array");
		MyArray* c = new MyArray("output", length);
		for (size_t i = 0; i < length; i++)
		{
			(*c)[i] = data[i] + b[i];
		}

		return c;
	}*/

	MyArray operator+(MyArray& b)
	{
		int j = 0;
		if (length != b.length)
			throw invalid_argument("array b must have the same dimension as input array");
		MyArray c("output", length);
		for (size_t i = 0; i < length; i++)
		{
			c[i] = data[i] + b[i];
		}

		return c;
	}

	~MyArray()
	{
		if (data != 0)
		{
			delete[] data;
		}
	}

private:
	_T* data;
	int length;
	std::string name;
};

