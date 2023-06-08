#include "MyArray.h"
#include <stdexcept>

void MyArray::initialize(unsigned int n, bool initialize_values /*= false*/, float value /* = 0 */)
{
	if (n > 0)
	{
		length = n;
		data = new float[n];
		if (initialize_values)
		{
			for (auto i = 0; i < n; i++)
			{
				data[i] = value;
			}
		}
	}
	else
		//std::cout << "invalid argument";
		throw std::invalid_argument("Array length must be greater than zero");
}

MyArray::~MyArray()
{
	if (length > 0 && data)
	{
		delete[] data;
		//data = nullptr;
		//length = 0;
	}
}

void MyArray::print()
{
	std::cout << "Array contains:" << std::endl;
	for (auto i = 0; i < length; i++)
	{
		std::cout << data[i] << ", ";
	}
	std::cout << std::endl;
}

float MyArray::get(unsigned int index)
{	
	if (index < length)
	{
		return data[index];
	}
	else
		//return 0;
		throw std::out_of_range("index is larger than array size");
}

void MyArray::set(unsigned int index, float val)
{
	if (index < length)
	{
		data[index] = val;
	}
	else
		//return 0;
		throw std::out_of_range("index is larger than array size");
}

//operator overloading
//سربارگذاری عملگرها
float& MyArray::operator[](int index)
{
	if (index < length)
		return data[index];
	else
		throw std::out_of_range("index is larger than array size");
}