#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename _VarType = float, typename _SizeType = unsigned long>
class SmartArray
{
public:
	SmartArray()
	{
		length = 0;
		data = nullptr;
	}
	SmartArray(_SizeType n, bool initialize_values = false, _VarType value = 0)
	{
		initialize(n, initialize_values, value);
	}

	//Copy Constructor (SmartArray a = other or SmartArray a(other))
	SmartArray(const SmartArray& other)
	{
		initialize(other.length, false);
		//کپی کردن داده ها از آرایه مبدا به آرایه مقصد
		std::copy(other.data, other.data + other.length, data);
		
		//کد فوق نسخه ساده و سریع کد زیر است
		//for (auto i = 0; i < length; i++)
		//	data[i] = copy[i];
	}

	//Copy assignment operator (a = other) "a" currently exists and has initialized
	SmartArray& operator=(const SmartArray& other)	
	{		
		if (this == &other) //protection against self-assignment 
			return *this;
		
		delete[] data;
		data = new _VarType[other.length];
		//کپی کردن داده ها از آرایه مبدا به آرایه مقصد
		std::copy(other.data, other.data + other.length, data);
		length = other.length;
		return *this;
	}

	//Move constrcutor
	//See https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
	SmartArray(SmartArray&& other);     // <-- rvalue reference in input

	//Move Assignment (only for study)
	SmartArray& operator=(SmartArray&& other);     // <-- rvalue reference in input (&&) 

	~SmartArray()//the only destructor
	{
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
			length = 0;
		}
	}

	void initialize(_SizeType n, bool initialize_values = false, _VarType value = 0);

	void set(int idx, _VarType val);


	_VarType get(int idx) const
	{
		if ((idx < length) && (idx >= 0))
			return data[idx];
		else
			throw out_of_range("index is larger than array size");
	}

	//Operator Overloading
	// subscript operator for const objects returns rvalue
	_VarType operator[](int index) const
	{
		return get(index);
	}

	//to set values
	_VarType& operator[](int idx)
	{
		if ((idx < length) && (idx >= 0))
			return data[idx];
		else
		{
			throw std::out_of_range("index out of range");
			//return fake_val;
		}
	}

	bool operator==(SmartArray& b)
	{
		if (this->length != b.length)
			return false;

		for (auto i = 0; i < length; i++)
		{
			if (data[i] != b[i])
				return false;
		}

		return true;
	}

	SmartArray& operator+=(SmartArray& b)
	{
		for (auto i = 0; i < length; i++)
			data[i] += b[i];

		return *this;
	}

	/*SmartArray& operator+(const SmartArray& b) const
	{
		SmartArray c(length, true);

		for (auto i = 0; i < length; i++)
			//c->set(i, data[i] + b[i]);
			c[i] = data[i] + b[i];

		return c;
	}*/

	SmartArray* operator+(const SmartArray& b) const
	{
		SmartArray* c = new SmartArray(length, true);

		for (auto i = 0; i < length; i++)
			//c->set(i, data[i] + b[i]);
			(*c)[i] = data[i] + b[i];

		return c;
	}

	void print()
	{
		cout << "Array contains: \n";
		for (auto i = 0; i < length; i++)
			cout << setw(7) << data[i] << ",";

		cout << "\n";
	}
private:
	_VarType* data = nullptr;
	_SizeType length = 0;
	//_T fake_val;
};


