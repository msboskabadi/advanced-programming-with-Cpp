// CPP06-SmartArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include <iostream>
#include <iomanip>
#include "SmartArray.h"

using namespace std;
using DArray = SmartArray<double, int>;

DArray createArray()
{
	return DArray(5, true, 5.0);
}

int main() try
{
	SmartArray<> f(5, true, 3.5);//float array
	SmartArray<double, int> p(3, true, 4.0);//double array
	SmartArray<double, int> q = p; //Copy constructor is called
	SmartArray<double, int> r(5, true, 5.0);
	r = p;//Copy assignment operator is called
	
	DArray s = std::move(r);//Move Constructor
	r.print();
	s.print();
	s = std::move(p); //Move Assignment
	p.print();
	s.print();
	DArray w = createArray();// move constructor (rvalue in input)
	w.print();
	q[2] = 5;
	q.print();
	p.print();
	r.print();

	DArray	a(3, true, 5.0);
	DArray b = a;
	b[2] = 7.0;
	a.print();
	b.print();

	a += b;
	a.print();

}
catch (std::out_of_range e)
{
	cout << e.what();
}
catch (std::invalid_argument e)
{
	cout << e.what();
}
catch (...)
{
	cout << "Something is wrong";
}