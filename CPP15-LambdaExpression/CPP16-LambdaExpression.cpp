
#include <iostream>

//Ref: https://www.geeksforgeeks.org/generalized-lambda-expressions-c14/
/*
C++ 11 introduced lambda expression to allow us write an inline function which can be 
used for short snippets of code that are not going to be reuse and not worth naming:

	[capture clause](parameters) -> return-type
	{
	   definition of method
	}
Generally return-type in lambda expression are evaluated by compiler itself and we 
don�t need to specify that explicitly.

C++ 14 introduced a generalized lambda. By combining a lambda expression with the 
*auto* keyword these expressions can then be later used in the program:
 	[](int a, int b) -> int { return a + b; }
	[](double a, double b) -> double { return a + b; }

Before C++ 14 there was a way to circumvent this problem by using template parameters,
	template<typename T>
	[](T a, T b) -> T { return a + b };

But in C++ 14 we can use auto:
	[](auto a, auto b) { return a + b; }
*/

#include <string>
#include <vector>
#include <algorithm> //sort
using namespace std;

// Utility Function to print the elements of a collection
//This auto only works in C++20!
void printElements(auto& C)
{

	for (auto e : C)
		cout << e << " ";

	cout << endl;
}

int main()
{
	//char* pEnd;
	//unsigned long long nc = strtoull("ffffffffffffffff", &pEnd, 16);
	//nc = sqrt(nc);
	//////////////////////////////////////////////////////////////////////////
	cout << "----------------------------------\n" << "Lambda sum example:\n";
	// Declare a generalized lambda and store it in sum 
	auto sum = [](auto a, auto b){
		return a + b;
	};

	// Find sum of two integers 
	cout << sum(1, 6) << endl;

	// Find sum of two floating numbers 
	cout << sum(1.0, 5.6) << endl;

	// Find sum of two strings 
	cout << sum(string("Advanced C++ "), string("Shahrood UT")) << endl;

	//////////////////////////////////////////////////////////////////////////
	cout << "\n----------------------------------\n" << "Sort example:\n";
	// Declare a generalized lambda and store it in greater 
	auto greater = [](auto a, auto b) -> bool {
		return (a > b);
	};

	// Initialize a vector of integers 
	vector<int> vi = { 1, 4, 2, 1, 6, 62, 636 };

	// Initialize a vector of doubles 
	vector<double> vd = { 4.62, 161.3, 62.26, 13.4, 235.5 };

	// Initialize a vector of strings 
	vector<string> vs = { "Hossein", "Ali", "Sajjad", "Mohammad" };

	// Sort integers 
	sort(vi.begin(), vi.end(), greater);

	// Sort doubles 
	sort(vd.begin(), vd.end(), greater);

	// Sort strings 
	sort(vs.begin(), vs.end(), greater);

	printElements(vi);
	printElements(vd);
	printElements(vs);


	//////////////////////////////////////////////////////////////////////////
	cout << "\n----------------------------------\n" << "Another example:\n";
	//Fig 16.1 Deitel 10'th edition
	const int size = 4; // size of array values
	int values[size] = { 1, 2, 3, 4 }; // initialize values
	int x = 20;
	// output each element multiplied by two
	for_each(values, values + size, 
		[](int i){ cout << i << "*2\t" << i * 2 << endl; });

	int total = 0; // initialize total to zero

	// add each element to total
	// Here lambda expression captures local variable (total) 
	for_each(values, values + size,
		[&total](int i) { total += i; });

	cout << "total is " << total << endl; // output total
}

