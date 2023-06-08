// CPP01-Basics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

namespace opencv
{
    void print()
    {
        std::cout << "OpenCV 4.5.5\n";
    }
}

namespace math
{
    void print()
    {
        std::cout << "Math 2.2.3\n";
    }
}

//using namespace opencv;
using opencv::print;
using std::cout;
using std::cin;
int main()
{
    std::cout << "Hello World!\n";
    print();
    math::print();

    float data[5]{ 2.5, 3.75, -5, 14, 19.5 };
    //for (int i = 0; i < 5; i++)
        //cout << data[i] << std::endl;

    for(auto v : data)
        cout << v << std::endl;

    float x, y;
    cout << "\nEnter 2 numbers:\n";
    cin >> x >> y;
    cout << "\n" << x << " + " << y << " = " << x + y;

    std::vector<int> v{ 7, 12, 10, -5, 14 };

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << "\n";


    for (auto d : v)
        cout << d << "\n";

    cout << "vector after push_back\n";
    v.push_back(17);
    v.push_back(18);

    for (auto d : v)
        cout << d << "\n";

    v.insert(v.begin() + 3, { 20, 13 });
    for (auto d : v)
        cout << d << "\n";
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
