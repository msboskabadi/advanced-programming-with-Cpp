// CPP15-STL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//STL: Standard Template Library

#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <deque>
#include <map>
#include <array>
#include <type_traits> //decltype
using namespace std;

//این کد فقط با استاندارد 2020 به بعد کار می کند
void print(auto data)
{
	for (auto v : data)
		cout << '\t' << v;
	cout << '\n';
}

template <class T1, class T2>
void print(const map<T1, T2>& a)
{
	for (auto i : a)
	{
		cout << '\t' << i.first
			<< '\t' << i.second << '\n';
	}
}

void showlist(list <int> g)
{
	for (auto it : g)
		cout << '\t' << it;
	cout << '\n';
}

void showdq(deque <int> g)
{
	for (auto it : g)
		cout << '\t' << it;
	cout << '\n';
}

int main()
{
	//array<int, 5> ar{ 1,2,3,4,5 };
	
#pragma region Vector Example
	//Vectors are containers with the ability to *RESIZE* when a new element is inserted or 
	//deleted from it. It is a template of Standard Template Library or STL which provides 
	//more flexibility to the program. 
	//Elements of vectors are placed in CONTIGUOUS storage and are traversed using iterators.

	vector<int> v{2, 7};
	// Inserting elements in vector
	v.push_back(11);
	v.push_back(6);
	v.push_back(12);
	v.push_back(0);
	v.push_back(0);
	// Elements are stored in the 
	// order of insertion with the 
	// duplicate element 
	cout << "Elements in vector are:\n";
	//for (int i = 0; i < v.size(); i++)
		//cout << v[i] << " ";

	print(v);

	vector<string> v2 {"Salaam", "Iran" };
	for (auto it : v2) {
		cout << it << " ";
	}
#pragma endregion

#pragma region Set Example
	//مجموعه ای از داده های یکتا به صورت مرتب شده
	//Set is also one of the templates of STL. It is a container of *UNIQUE* elements whose 
	//value can’t be modified once added to the set but can be deleted or inserted.
	//The elements of the sets are always stored in *SORTED* form.
	set<int> s;

	// Insert elements into the set 
	s.insert(11);
	s.insert(11);
	s.insert(6);
	s.insert(5);
	s.insert(12);
	s.insert(0);

	// Duplicate elements 
	s.insert(0);

	cout << "\n\nElements in set:\n";

	// The inserted elements get sorted 

	// Print the elements of the set 
	print(s);
#pragma endregion

#pragma region List Example
	//Lists are sequence containers that allow *NON-CONTIGUOUS MEMORY ALLOCATION*.
	//As compared to vector, list has *SLOW* traversal, but once a position has been found, 
	//insertion and deletion are *QUICK*. 
	//Normally, when we say a List, we talk about *DOUBLY LINKED LIST*.
	list <int> list1, list2;

	for (int i = 0; i < 5; ++i)
	{
		list1.push_back(i * 2);
		list2.push_front(i * 2);
	}
	cout << "\n\nList 1 is : ";
	print(list1);

	cout << "\nList 2 is : ";
	print(list2);

	cout << "\nlist1.front() : " << list1.front();
	cout << "\nlist1.back() : " << list1.back();

	cout << "\nlist1.pop_front() : ";
	list1.pop_front();
	showlist(list1);

	cout << "\nlist2.pop_back() : ";
	list2.pop_back();
	showlist(list2);

	cout << "\nlist1.reverse() : ";
	list1.reverse();
	showlist(list1);

	cout << "\nlist2.sort(): ";
	list2.sort();
	showlist(list2);
#pragma endregion

#pragma region Deque Example

	//Double ended queues are sequence containers with the feature of expansion and contraction on both the ends.
	//They are similar to vectors, but are more efficient in case of INSERTION AND DELETION of elements.
	//Unlike vectors, contiguous storage allocation may not be guaranteed.

	deque <int> quiz;
	quiz.push_back(10);
	quiz.push_front(20);
	quiz.push_back(30);
	quiz.push_front(15);
	cout << "The deque quiz is : ";
	showdq(quiz);

	cout << "\nquiz.size() : " << quiz.size();
	cout << "\nquiz.max_size() : " << quiz.max_size();

	cout << "\nquiz.at(2) : " << quiz[2];// .at(2);
	cout << "\nquiz.front() : " << quiz.front();
	cout << "\nquiz.back() : " << quiz.back();

	cout << "\nquiz.pop_front() : ";
	quiz.pop_front();
	showdq(quiz);

	cout << "\nquiz.pop_back() : ";
	quiz.pop_back();
	showdq(quiz);
#pragma endregion

#pragma region Map Example

	//Maps are associative containers that store elements in a mapped fashion.
	//Each element has a key value and a mapped value.
	//No two mapped values can have same key values.
	//The elements of the maps are always stored in *SORTED* form.
	// empty map container 
	map<int, int> map1;

	// insert elements in random order 
	map1.insert(pair<int, int>(10, 40));
	map1.insert({2, 30});
	map1.insert({3, 60});
	map1.insert({4, 20});
	map1.insert({5, 50});
	map1.insert({6, 160});
	map1.insert({7, 10});

	// printing map map1 
	map<int, int>::iterator itr;
	cout << "\nThe map map1 is : \n";
	cout << "\tKEY\tELEMENT\n";
	print(map1);

	/*for (itr = map1.begin(); itr != map1.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}

	for (auto i : map1)
	{
		cout << '\t' << i.first
			<< '\t' << i.second << '\n';
	}*/

	cout << endl;

	// assigning the elements from map1 to map2 
	map<int, int> map2(map1.begin(), map1.end());

	// print all elements of the map map2 
	cout << "\nThe map2 after"
		<< " assign from map1 is : \n";
	cout << "\tKEY\tELEMENT\n";
	print(map2);
	cout << endl;

	// remove all elements up to 
	// element with key=3 in map2 
	cout << "\nmap2 after removal of"
		" elements less than key=3 : \n";
	cout << "\tKEY\tELEMENT\n";
	map2.erase(map2.begin(), map2.find(3));
	print(map2);

	// remove all elements with key = 4 
	int num;
	num = map2.erase(4);
	cout << "\nmap2.erase(4) : ";
	cout << num << " removed \n";
	cout << "\tKEY\tELEMENT\n";
	print(map2);

	cout << endl;

	// lower bound and upper bound for map map1 key = 5 
	cout << "map1.lower_bound(5) : "
		<< "\tKEY = ";
	cout << map1.lower_bound(5)->first << '\t'; //iterator to the beginning of key 5
	cout << "\tELEMENT = "
		<< map1.lower_bound(5)->second << endl;
	cout << "map1.upper_bound(5) : "
		<< "\tKEY = ";
	cout << map1.upper_bound(5)->first << '\t';//iterator after the key 5!
	cout << "\tELEMENT = "
		<< map1.upper_bound(5)->second << endl;


	map<string, int> map3;
	map3.insert({ "tehran"  , 21 });
	map3.insert({ "mashahad", 51 });
	map3.insert({ "semnan"  , 23 });
	print(map3);

#pragma endregion
	return 0;
}