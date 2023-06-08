
#include <iostream>
#include <memory> // for std::unique_ptr

//اشاره گرهای هوشمند به منظور آسان کردن مدیریت حافظه و کم کردن زحمت برنامه نویسان ایجاد شده اند
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////
//sample1: std::unique_ptr
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }

    friend std::ostream& operator<<(std::ostream& out, const Resource& res)
    {
        out << "I am a resource\n";
        return out;
    }
};

//تابع زیر سبب نشت حافظه می شود چرا که قبل از آزاد شدن اشاره گر، استثنا رخ داده و کد ادامه نمی یابد
void someFunction()
{
    auto* ptr{ new Resource() };

    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        throw 0; // the function returns early, and ptr won’t be deleted! MEMORY LEAK

    // It would be great if the dynamic memory pointed to by the pointers could be freed 
    // like variables and normal objects that disappear when they are out of scope.
    // This is the task of SMART POINTERS

    delete ptr;
}

int sample1()
{
    // allocate a Resource object and have it owned by std::unique_ptr
    std::unique_ptr<Resource> res1{ new Resource() };// Resource created here
    
    //avoid using like this
    //Resource* p = new Resource();
    //std::unique_ptr<Resource> res3{ p };// Resource created here

    /*
    * Ownership of pointer to unique_ptr
    * It is not possible for two unique_ptr objects to manage the same pointer. 
    * For this reason, this class has disabled copy functions.
    * Therefore, in order to make the content of an object of unique_ptr equal to another object of 
    * the same class, we must consider two points:
    *    We must use move semantics. Therefore, if our value is not an r-value, we must use std::move.
    *    After this, our primary object (on the right side of the = sign) is considered an empty object.
    */
        
    std::unique_ptr<Resource> res2{}; // Start as nullptr
    
    //static_cast<bool>(res1) is simply the new typecasting! it can be deleted!
    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
    std::cout << "res2 is " << ((res2 != nullptr) ? "not null\n" : "null\n");

    // res2 = res1; // Won't compile: copy assignment is disabled
    res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
    std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//sample2: std::make_unique
class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int numerator = 0, int denominator = 1) :
        m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
        out << f1.m_numerator << '/' << f1.m_denominator;
        return out;
    }
};

int sample2()
{
    /*
    * std::make_unique
    * This class, which was added in C++ 14, makes it possible to work with unique_ptr easily
    * and also avoids possible problems such as unwanted change of the main pointer (which the unique_ptr class is maintaining).
    */

    // Create a single dynamically allocated Fraction with numerator 3 and denominator 5
    auto f1{ std::make_unique<Fraction>(3, 5) };
    std::cout << *f1 << '\n';

    // Create a dynamically allocated array of Fractions of length 4
    auto f2{ std::make_unique<Fraction[]>(4)};
    std::cout << f2[3] << '\n';
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//sample3: Passing unique_ptr to a function

/*
* This class has disabled the functions related to copy, so by using move semantics, 
* when the transfer is done, the primary object is no longer responsible for managing 
* the corresponding memory.
* Therefore, if we pass an object of this class to a function using move, 
* its ownership is transferred to the object inside the function, and when that function is finished, 
* our memory (allocated outside the function) is freed.
* To avoid this problem, it is better to use the get() function.
*/

// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void useResource(Resource* res)
{
    if (res)
        std::cout << "useResource " << *res << '\n';
}

//by value (ownership transfers)
void useResource2(unique_ptr<Resource> res)
{
    if (res)
        std::cout << "useResource2 " << *res << '\n';
}

//by reference (ownership doesn't transfer)
void useResource3(unique_ptr<Resource>& res)
{
    if (res)
        std::cout << "useResource2 " << *res << '\n';
}

int sample3()
{
    auto ptr{ std::make_unique<Resource>() };
    auto ptr2{ std::make_unique<Resource>() };

    auto pp = ptr.get();
    //useResource( ptr); // Error
    useResource(ptr.get()); // note: get() used here to get a pointer to the Resource
    useResource2(std::move(ptr)); // ownership transfered
    useResource(ptr.get()); // ptr is empty

    useResource3(ptr2); // ownership not transfered
    useResource(ptr2.get()); // ptr2 is not empty

    std::cout << "Ending program\n";
    return 0;
}

int main()
{
    sample1();
    sample2();
    sample3();
}