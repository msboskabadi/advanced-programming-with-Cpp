// CPP05-Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
class Car
{
public:
	Car(string brand = "", string model = "", int year = 1398)
	{
		set_data(brand, model, year);
	}
	void set_data(string brand = "", string model = "", int year = 1398)
	{
		this->brand = brand;
		this->model = model;
		this->year = year;
	}

	void print()
	{
		std::cout << brand << "\t" << model << "\t" << year << "\n";
	}

private:
	string brand;
	string model;
	int year;
};

int main()
{
	int z = 10;
	int* w = &z;
	*w = 11;
	//delete w;


	int* p0 = new int[20];//تخصیص 20 خانه صحیح به اشاره گر
	int* q0 = new int(20);//تخصیص یک خانه صحیح به اشاره گر با مقدار 20

	delete[] p0;
	delete q0;

	Car dena("IKCO", "Dena+", 1399);//نمونه سازی عادی - ایستا
	dena.print();

	Car* p207 = new Car("IKCO", "207", 1397);//نمونه سازی پویا
	p207->print();

	delete p207;

	Car* Prides = new Car[100];
	
	Prides[0].set_data("Saipa", "131", 1397);
	Prides[0].print();
	
	Prides[1].set_data("Saipa", "Tiba", 1400);
	Prides[1].print();

	delete[] Prides;
	
	//return 0;

	int x = 10;
	int* px = &x;
	//delete px; //Error
	printf("x = %d and is located at address %p\n", x, px);

	//char a[10*1000*1000];

	char* p = new char[500 * 1000 * 1000];
	p[0] = 'A';
	p[9] = 'Z';

	delete[] p;
	std::cout << "Hello World!\n";
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
