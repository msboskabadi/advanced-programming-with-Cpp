#include "SmartArray.h"

#define temp_var_sz template<typename _VarType, typename _SizeType> 
#define SArray SmartArray<_VarType, _SizeType>

temp_var_sz
void SArray::set(int idx, _VarType val)
{
	if ((idx < length) && (idx >= 0))
	{
		data[idx] = val;
	}
	else
		throw out_of_range("index is larger than array size");
}

temp_var_sz
void SArray::initialize(_SizeType n, bool initialize_values /*= false*/, _VarType value /*= 0*/)
{
	if (n > 0)
	{

		length = n;
		data = new _VarType[n];
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

//Move contrcutor (only for study)
//See https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
temp_var_sz
SArray::SmartArray(SmartArray&& other)     // <-- rvalue reference in input
{
	data = other.data;   // steal data from rvalue reference (instead of deep copy)
	length = other.length;
	other.data = nullptr;  //set other data to null
	other.length = 0;
}

//Move Assignment (only for study)
temp_var_sz
SArray& SArray::SmartArray::operator=(SmartArray&& other)     // <-- rvalue reference in input  
{
	if (this == &other) return *this;

	delete[] data;       // (1)

	data = other.data;   // steal data from the other object coming in as an rvalue reference
	length = other.length;

	other.data = nullptr;// put the temporary object to some valid state
	other.length = 0;

	return *this;
}

template class SmartArray<float, unsigned long>;
template class SmartArray<int, int>;
template class SmartArray<double, int>;