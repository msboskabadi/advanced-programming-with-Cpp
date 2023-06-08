// C++ Programming
// Shahrood University of Technoloy
// Hossein Khosravi - 2023

/* 
 * shared_ptr works in such a way that it remembers the number of objects that are holding 
 * a certain memory and only releases that memory when the last holding object wants to be destroyed.
 */
#include <iostream>
#include <memory> // for std::shared_ptr
using namespace std;
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int sample1()
{
	std::cout << "\n Sample 1 -------------------------------------------------\n";
	// allocate a Resource object and have it owned by std::shared_ptr
    Resource* res = new Resource;
    std::shared_ptr<Resource> ptr1(res);
    {
        std::shared_ptr<Resource> ptr2(ptr1); // use copy initialization to make another std::shared_ptr pointing to the same thing
        // To create ptr2, we must pass ptr1 to copy. If we give it the res by mistake, 
        // those two objects will no longer recognize each other and ptr2 will delete the memory it took.

        std::cout << "Killing one shared pointer\n";
    } // ptr2 goes out of scope here, but nothing happens

    std::cout << "Killing another shared pointer\n";

    return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed


////////////////////////////////////////////////////////////////////////////
//make_shared
int sample2()
{
	std::cout << "\n Sample 2 -------------------------------------------------\n";
	// allocate a Resource object and have it owned by std::shared_ptr
    auto ptr1 = std::make_shared<Resource>();
    {
        auto ptr2 = ptr1; // create ptr2 using copy initialization of ptr1

        std::cout << "Killing one shared pointer\n";
    } // ptr2 goes out of scope here, but nothing happens

    std::cout << "Killing another shared pointer\n";

    return 0;
} 

////////////////////////////////////////////////////////////////////////////
struct Foo {
    Foo(int n = 0) noexcept : bar(n) {
        std::cout << "Foo::Foo(), bar = " << bar << " @ " << this << '\n';
    }
    ~Foo() {
        std::cout << "Foo::~Foo(), bar = " << bar << " @ " << this << "\n";
    }
    int getBar() const noexcept { return bar; } //noexcept: this method doesn't require try-catch
private:
    int bar;    
};

////////////////////////////////////////////////////////////////////////////
int sample3()
{
	std::cout << "\n Sample 3 -------------------------------------------------\n";
	std::cout << "1) unique ownership\n";
	{
		std::shared_ptr<Foo> sptr = std::make_shared<Foo>(100);

		std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
			<< sptr.use_count() << '\n';

		// Reset the shared_ptr without handing it a fresh instance of Foo.
		// The old instance will be destroyed after this call.
		std::cout << "call sptr.reset()...\n";
		sptr.reset(); // calls Foo's destructor here
		std::cout << "After reset(): use_count() = " << sptr.use_count()
			<< ", sptr = " << sptr << '\n';
	}   // No call to Foo's destructor, it was done earlier in reset().

	std::cout << "\n2) unique ownership\n";
	{
		std::shared_ptr<Foo> sptr = std::make_shared<Foo>(200);

		std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
			<< sptr.use_count() << '\n';

		// Reset the shared_ptr, hand it a fresh instance of Foo.
		// The old instance will be destroyed after this call.
		std::cout << "call sptr.reset()...\n";
		sptr.reset(new Foo{ 222 });
		std::cout << "After reset(): use_count() = " << sptr.use_count()
			<< ", sptr = " << sptr << "\nLeaving the scope...\n";
	}   // Calls Foo's destructor.

	std::cout << "\n3) multiple ownership\n";
	{
		std::shared_ptr<Foo> sptr1 = std::make_shared<Foo>(300);
		std::shared_ptr<Foo> sptr2 = sptr1;
		std::shared_ptr<Foo> sptr3 = sptr2;

		std::cout << "Foo::bar = " << sptr1->getBar() << ", use_count() = "
			<< sptr1.use_count() << '\n';

		// Reset the shared_ptr sptr1, hand it a fresh instance of Foo.
		// The old instance will stay shared between sptr2 and sptr3.
		std::cout << "call sptr1.reset()...\n";
		sptr1.reset(new Foo{ 313 });

		std::cout << "After reset():\n"
			<< "sptr1.use_count() = " << sptr1.use_count()
			<< ", sptr1 @ " << sptr1 << '\n'
			<< "sptr2.use_count() = " << sptr2.use_count()
			<< ", sptr2 @ " << sptr2 << '\n'
			<< "sptr3.use_count() = " << sptr3.use_count()
			<< ", sptr3 @ " << sptr3 << '\n'
			<< "Leaving the scope...\n";
	}   // Calls two destructors of: 1) Foo owned by sptr1,
		// 2) Foo shared between sptr2/sptr3.
	return 0;
}

////////////////////////////////////////////////////////////////////////////
// FOR STUDY
// using our imaplementation of shared_ptr
#include "MySharedPtr.h"
void sample4()
{
	std::cout << "\n Sample 3 -------------------------------------------------\n";

	my_shared_ptr<Resource> obj;
	cout << obj.get_count() << endl; // prints 0
	my_shared_ptr<Resource> box1(new Resource());
	cout << box1.get_count() << endl; // prints 1
	my_shared_ptr<Resource> box2(box1); // calls copy constructor
	{
		my_shared_ptr<Resource> box3(box1); // calls copy constructor
		cout << box1.get_count() << endl; // prints 3
	}
	cout << box1.get_count() << endl; // prints 2
	cout << box2.get_count() << endl; // also prints 2
}
int main()
{
    sample1();
	sample2();
	sample3();
	sample4(); //Myshared_ptr
    //weak_ptr
    std::shared_ptr<int> sp0(new int(5));
    std::weak_ptr<int> wp0(sp0);
    
	std::cout << "\n WeakPtr -------------------------------------------------\n";
	//To access element of a weak_ptr we cannot use *sp0. Try like this:
	//lock: Obtains a shared_ptr that shares ownership of a resource.
    std::weak_ptr<int>::element_type val = *wp0.lock();
    std::cout << "*wp0.lock() == " << val << std::endl;
    
    sp0.reset();
    std::cout << "expired = " << std::boolalpha << wp0.expired() << std::endl;
}
