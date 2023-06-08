// CPP05-MyArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyArray.h"
#include <array>
int main()
{    
    array<float, 5> w{ 1,2,3,4,5 };
    MyArray<int> a("A", 10, true, 5);
    MyArray<int> b("B", 10, true, 2);
    a.print();
    a[5] = 10;
    a += 3;
    a.print();
    b.print();
    b += a;
    b.print();
    //b.resize(5);
    b.print();
    //b.resize(7);
    b.print();
    cout << b.size();
    MyArray<int> d = a + b;
    d.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
