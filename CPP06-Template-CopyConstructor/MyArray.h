#pragma once
#include <iostream>

class MyArray
{
public:
	MyArray()
	{
		length = 0;
		data = nullptr;
	}

	MyArray(unsigned int n, bool initialize_values = false, float value = 0)
	{
		initialize(n, initialize_values, value);
	}

	void print();


	~MyArray();

	void initialize(unsigned int n, bool initialize_values = false, float value = 0);

	unsigned int get_size() { return length; }
	
	float get(unsigned int index);
	void set(unsigned int index, float val);

	float& operator[](int index);

private:
	// pointer for memory allocation
	float* data;
	int length;
};

