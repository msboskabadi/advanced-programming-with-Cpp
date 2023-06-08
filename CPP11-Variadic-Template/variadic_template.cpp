
#include <iostream>
#include <vector>

using namespace std;

void print() {
    cout << endl;
}

//template <typename T>
//void print(const T& t) {
//    cout << t << endl;
//}

template <typename First, typename... Rest>
void print(const First& first, const Rest&... rest) {
    cout << first << ", ";
    print(rest...); // recursive call using pack expansion syntax
}

////////////////////////////////////////////////////////
//A function that adds all of its arguments together :
template<typename T>
T adder(T v) {
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
    return first + adder(args...);
}

int main()
{
    std::vector<int> arr;

    long sum = adder(1, 2, 3, 8, 7);

    string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
    string ssum = adder(s1, s2, s3, s4);
    cout << ssum << endl;

    //print(); // calls first overload, outputting only a newline
    print(1); // calls second overload

    // these call the third overload, the variadic template,
    // which uses recursion as needed.
    print<int, int>(10, 20);
    print(10, 20);
    print(100, 200, 300);
    print<string, int, string, float>("first", 2, "third", 3.14159);
    print("first", 2, "third", 3.14159);
}

//https://docs.microsoft.com/en-us/cpp/cpp/ellipses-and-variadic-templates?view=msvc-170

