// Friendship.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// friend functions
#include <iostream>
using namespace std;

#define BASIC_VERSION

/*#ifdef TRIAL
std::string version = "Trial";
#elif defined BASIC_VERSION
std::string version = "Basic";
#else
std::string version = "Pro";
#endif*/



#if 0
class Rectangle 
{
private:
	int width, height;
public:
	Rectangle() {}
	Rectangle(int x, int y) : width(x), height(y) {}
	int area() { return width * height; }
	friend Rectangle duplicate(const Rectangle&);
};

Rectangle duplicate(const Rectangle& param)
{
	Rectangle res;
	res.width = param.width * 2;
	res.height = param.height * 2;
	return res;
}

int main() {
	
	Rectangle r1(2, 3);
	Rectangle r2 = duplicate(r1);
	cout << r2.area() << '\n';
	return 0;
}
#else

//class Square;

class Rectangle
{
	friend class Square;
	friend Rectangle duplicate(const Rectangle& rc);
private:
	int width, height;
public:
	Rectangle (int w = 0, int h = 0):width(w), height(h){}
	int area()
	{
		return (width * height);
	}
	void convert(Square a);

	void print()
	{
		std::cout << "w = " << width << ", h = " << height << endl;
	}
};

class Square {
	friend class Rectangle;
private:
	int side;
public:
	Square(int a) : side(a) {};
	void shrink_from_rect(Rectangle rc)
	{
		side = (rc.width < rc.height) ? rc.width : rc.height;
	}

	void print()
	{
		std::cout << "side = " << side << endl;
	}
};

void Rectangle::convert(Square a) {
	width = a.side;
	height = a.side;
}

Rectangle duplicate(const Rectangle& rc)
{
	Rectangle out;
	out.width = rc.width * 2;
	out.height = rc.height * 2;

	return out;
}

int main() {
	Rectangle rect;
	Square sqr(4);
	rect.convert(sqr);
	cout << rect.area() << endl;

	Rectangle r2(10, 20);
	sqr.shrink_from_rect(r2);
	sqr.print();
	
	Rectangle r3 = duplicate(r2);
	r3.print();

	return 0;
}
#endif