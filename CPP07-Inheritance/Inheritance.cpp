// Inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
using ull = unsigned long long;

class Person
{
public:
    Person(string name, ull nat_code): name(name), nat_code(nat_code)
    {
        count++;
    }

    virtual void print()
    {
        cout << "count = " << count << endl;
        cout << name << endl << nat_code << endl;
    }

    //متغیر ایستا در سطح کلاس تعریف می شود و انحصارا متعلق به هیچ شیئی نیست
    static int count;

    static void print_count()
    {
        cout << "count = " << count << endl;
    }
    ~Person()
    {
        count--;
    }
private:
    string name;
    ull nat_code;
};

int Person::count = 0;

class Student : public Person
{
public:
    Student(string name, ull nat_code, ull id):
        Person(name, nat_code), st_id(id)
    {
        
    };

    void print()
    {
        cout << "(student) ";
        Person::print();
        cout << st_id << endl;
    }

private:
    ull st_id;
};

class Employee : public Person
{
public:
    Employee(string name, ull nat_code, ull salary) :
        Person(name, nat_code), salary(salary)
    {

    };

    void print()
    {
        cout << "(employee) ";
        Person::print();
        cout << "Salary = " << salary << endl;
    }

private:
    ull salary;
};

int main()
{
    Person::print_count();
    Person p1("Abbas Askari", 9865321470);
    p1.print();
    Person p2("Bababk Jafari", 7097521003);
    p2.print();
    Student s1("Ali Hosseini", 8524137961, 40023512);
    s1.print();
    Employee e1("Akbar Sina", 2132004560, 15000000);
    e1.print();

    Person* p3 = new Person("Dynamic Person", 1000235469);
    //delete p3;
    //p3 = 0;
    //Person::print_count();

    //Polymorphism چندریختی
    Person* q1 = new Student("Student A", 1234567890, 78123818);
    q1->print();
}