// CPP02-CRect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;
struct Point
{
	float x;
	float y;
};


struct Triangle
{
	Point A, B, C;
};

class Book
{
public:
	//char author[30];
	string author;
	char name[50];
	int pages;
	int year;
	float price;

	void print()
	{
		cout << "\nBook name: " << name << "\n";
		cout << "Author: " << author << "\n";
		cout << "Pages: " << pages << "\n";
		cout << "Publish Year: " << year << "\n";
		cout << "Price: " << price << "\n";
	}
};

void print_book(Book& b)
{
	cout << "\nBook name: " << b.name << "\n";
	cout << "Author: " << b.author << "\n";
	cout << "Pages: " << b.pages << "\n";
	cout << "Publish Year: " << b.year << "\n";
	cout << "Price: " << b.price << "\n";
}

int main()
{
	float x1, y1;
	float x2, y2;
	float x3, y3;
	x1 = 10;
	y1 = 20;

	Point p1, p2 = { 15, 25 }, p3;
	p1.x = 10;
	p1.y = 20;

	Point p[3];

	//Declare a triangle with vertices located at (10, 20), (30, 40), (30, 60)
	Triangle t = { {10, 20}, {30, 40}, {30, 60} };
	t.A.x = 10;
	t.A.y = 20;
	t.B.x = 30;
	t.B.y = 40;
	t.C.x = 30;
	t.C.y = 60;


	Book b1 = { "Hossein Khosravi", "C++ Programming", 300, 1401, 25632 };
	Book b2 = { "Deitel & Deitel", "C++ How To Program", 1000, 1401, 300 };

	print_book(b1);
	print_book(b2);

	//strcpy_s(b1.author, 30, "Deitel");
	b1.author = "Deitel";

	//print_book(b1);
	b1.print();
}