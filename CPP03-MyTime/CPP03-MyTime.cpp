// CPP03-MyTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MyTime.h"

int main()
{
    MyTime t;
    MyTime* t2 = 0;
    try {
        t.set_hour(10).set_minute(32).set_second(10);

        t2 = new MyTime(17, 31, 15);
        t2->print();
        t2->print_standard();
        delete t2;
    }
    catch (std::exception e)
    {
        std::cout << e.what() << endl;
    }

    t.print();
    return 0;
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
