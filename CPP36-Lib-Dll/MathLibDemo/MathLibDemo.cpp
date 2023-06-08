// MathLibDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MathDll.h"
#include <iostream>

//float mean(float* data, int N);
#pragma comment(lib, "Mathlib.lib")
int main()
{
	float data[] = { 10, 20, 25, 30 };

	float m = mean(data, 4);

	std::cout << "mean = " << m << "\n";
    return 0;
}

