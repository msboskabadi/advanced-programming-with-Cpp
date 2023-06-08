// Pair_Tuple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

using Data = tuple<int, float, string>;
Data MultiOutput()
{
    //return make_tuple(12, 19.75, "Salaam");
    return { 12, 17.5, "Shahrood" };
}

using Result = pair<string, float>; //زوجی از یک رشته و یک اعشاری

Result TwoOutput()
{
    //return make_pair("IRAN", 20);
    return { "IRAN", 1404 };
}

int main()
{
    auto result = TwoOutput();
    cout << result.first << " " << result.second << endl;

	auto r = MultiOutput();
    
    cout << get<0>(r) << ", " << get<1>(r) << ", " << get<2>(r);
}
