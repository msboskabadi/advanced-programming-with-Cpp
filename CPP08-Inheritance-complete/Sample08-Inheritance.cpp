// Sample08-Inheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Person
{
public:
	Person(string name="", string nat_code=""):
		name(name), nat_code(nat_code)
	{
		person_count++;
		//this->name = name;
		//this->nat_code = nat_code;
	}

	void initialize(string name, string nat_code)
	{
		this->name = name;
		this->nat_code = nat_code;
	};

	virtual void print()
	{
		cout << "\nname: " << name << "\n" << "national code: " << nat_code << "\n";
		print_count();
	};

	//تابع ایستا فقط می تواند با متغیرهای ایستا کار کند و حق دسترسی به متغیرهای عادی کلاس را ندارد
	static void print_count()
	{
		cout << "person count = " << person_count << "\n";		
	}
	
	static int person_count;//متغیر ایستا متغیر سطح کلاس است و متعلق به هیچ شیئی نیست
protected:
	string name;
	string nat_code;
};

int Person::person_count = 0;

//وقتی کلاس به صورت عمومی مشتق می شود
//داده های عمومی کلاس پدر در کلاس فرزند عمومی هستند
//داده های حفاظت شده در کلاس فرزند به صورت خصوصی خواهند بود
//داده های خصوصی کلاس پدر در کلاس فرزند غیر قابل دسترس هستند
//public --> public
//protected --> private
//private --> inaccessible
class Student : public Person
{
public:
	Student(string name, string nat_code, int sid) :
		Person(name, nat_code), student_id(sid)
	{
		student_count++;
	}

	virtual void print()
	{
		Person::print();
		cout << "student id : " << student_id << "\n";
		//cout << "student count : " << student_count << "\n";
	}
	static void print_count()
	{
		cout << "student count is " << student_count << "\n";
	}
	static int student_count;
private:
	int student_id;
};

int Student::student_count = 0;

class Employee : public Person
{
public:
	Employee(string name, string nat_code, float salary) :
		Person(name, nat_code), base_salary(salary)
	{

	}
	float calc_salary(int hours_worked) 
	{
		float hourly_pay = base_salary / 192.0f;
		return base_salary + (hours_worked - 192) * hourly_pay * 1.4f;
	}
	void print_salary(int h)
	{
		cout << "salary is : " << calc_salary(h) << "\n";
	}
	virtual void print()
	{
		Person::print();
		cout << "Base Salary : " << base_salary << "\n";
	}
private:
	float base_salary;
};

int main()
{
	Person::print_count();
	cout << Person::person_count;

	Person a1("Ali Abbasi", "088-9632-581");
	Person::print_count();
	Person a2("Hossein Abbasi", "089-9632-581");

	Student std("Hossein Jafari", "197-2252-126", 9423215);

	Person::print_count();
	a1.print_count();


	Student::print_count();

	cout << "Person Count = " << Person::person_count << "\n";
	Person p("Ali Abbasi", "088-9632-581");	
	cout << "Person Count = " << p.person_count << "\n";		
	//cout << "\t COUNT = " << Person::person_count << "\n";


	p.print();
	Person p_2("Ali Abbasi", "088-9632-581");
	p_2.print();
	Person p_3("Ali Abbasi", "088-9632-581");
	p_3.print();

	Student s("Hossein Jafari", "197-2252-126", 9423215);
	Employee e("Hossein Khosravi", "100-2382-127", 2000);

	Person::print_count();
	Student::print_count();

	p.print();
	s.print();
	e.print();
	e.print_salary(200);

	Person* p2 = new Person("Parham Hajimohammadi", "123456789");
	(*p2).print();
	p2->print();

	//در استاندارد جدید امکان مقدار دهی اولیه به آرایه اشاره گری وجود دارد
	int* number = new int[5]{ 20, 20, 20, 20, 20 };
	for (size_t i = 0; i < 5; i++)
	{
		cout << number[i] << "\n";
	}

	Person* persons = new Person[10]{Person("Ali Gholami", "65498732158"), 
		Person("Akbar Abdi", "56248965312") };
	//persons[0].initialize("Ali Gholami", "65498732158");
	persons[0].print();
	persons[1].print();
	persons[2].print();


	//char* ptr = new char[1000];
	//
	//ptr++; //1 byte memory leak
	//
	//delete[] ptr;

	delete[] persons;
	delete p2;


	//Person person_array[50];
	//Person* person_pointer_array[50];

	//polymorphism
	Person* parray[3];
	parray[0] = new Person("Ali Hosseini", "123456789");
	parray[1] = new Student("Some Student", "321654987", 123654);
	parray[2] = new Employee("Some Employee", "654987321", 2000);
	for (size_t i = 0; i < 3; i++)
	{
		parray[i]->print();
	}

	return 0;
}

