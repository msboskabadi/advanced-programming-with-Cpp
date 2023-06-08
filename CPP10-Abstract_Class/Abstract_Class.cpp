// CPP08_Abstract_Class.cpp : Defines the entry point for the console application.
//

#include "pch.h"
// abstract base class
#include <iostream>
#include <string>

using namespace std;


//train
//predict
//forward
//backward
//...
//input data
//learning rate
//

class CPolygon {
public:
	/*CPolygon(int a, int b)
	{
		set_values(a, b);
	}*/

	void set_values(int a, int b)
	{
		width = a; 
		height = b;
	}
	virtual int area(void) = 0; //makes the class to be abstract (we cannot instantiate from this class)

protected:
	int width, height; //متغیرهایی که در تمام فرزندها مورد نیازند
};

class CRectangle : public CPolygon {
public:
	int area(void)
	{
		return (width * height);
	}
};

class CTriangle : public CPolygon {
public:
	int area(void)
	{
		return (width * height / 2);
	}
};


int main() 
{	
	CPolygon* p = new CTriangle();
	p->set_values(10, 12);
	
	CRectangle rect;
	CTriangle trgl;
	CPolygon * ppoly1 = &rect;
	CPolygon * ppoly2 = &trgl;
	ppoly1->set_values(4, 5);
	ppoly2->set_values(4, 5);
	cout << ppoly1->area() << endl;
	cout << ppoly2->area() << endl;
	return 0;
}