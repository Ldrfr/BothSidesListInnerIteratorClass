#include <iostream>
#include <cstring>

#include "both_sides_list.h"


void TestAll();
void TestInsertBefore();
void TestAddFirst();
void TestAddLast();
void TestDeleteNode();
void TestListConcatenation();
void TestCopyListConstructor();
void TestListEqual();
void TestListOfLists();

void TestAll() {
	TestInsertBefore();
	TestAddFirst();
	TestAddLast();
	TestDeleteNode();
	TestCopyListConstructor();
	TestListConcatenation();
	TestListEqual();
	TestListOfLists();
}

void TestAddFirst() {
	std::cout << "TestAddFirst\n";
	List<int> a;
	a.AddFirst(9);
	std::cout << a << "\n";
	List<int> b;
	b.AddFirst(17);
	b.AddFirst(6);
	std::cout << b << "\n";
}

void TestAddLast() {
	std::cout << "TestAddLast\n";
	List<int> a;
	a.AddLast(9);
	std::cout << a << "\n";
	List<int> b;
	b.AddLast(17);
	b.AddLast(6);
	std::cout << b << "\n";
}

void TestInsertBefore() {
	std::cout << "TestInsertBefore\n";
	List<int> a;
	a.AddFirst(17);
	a.AddFirst(6);
	a.AddFirst(10);
	std::cout << a << "\n";
	List<int>::Iterator it = a.FindFirstElementByValue(6);
	a.InsertBefore(it, -2);
	std::cout << "Insert -2 before 6\n" << a << "\n";
	it = a.FindFirstElementByValue(10);
	a.InsertBefore(it, -1);
	std::cout << "Insert -1 before 10 (first element)\n" << a << "\n";
	it = a.FindFirstElementByValue(17);
	a.InsertBefore(it, -3);
	std::cout << "Insert -3 before 17 (last element)\n" << a << "\n";
	/*
	it = a.FindFirstElementByValue(-100);
	a.InsertBefore(it, -4);
	std::cout << "Insert -4 before -100 (no such element)\n" << a << "\n";
	*/
	std::cout << a.GetValue(it) << "\n";
}

void TestDeleteNode() {
	std::cout << "TestDeleteNode\n";
	List<int> a;
	a.AddFirst(17);
	a.AddFirst(6);
	a.AddLast(375);
	List<int>::Iterator it;
	std::cout << a << "Now delete process:\n";
	it = a.FindFirstElementByValue(17);
	a.DeleteNode(it);
	std::cout << a << "\n";
	it = a.FindFirstElementByValue(6);
	a.DeleteNode(it);
	std::cout << a << "\n";
	it = a.FindFirstElementByValue(6); // trash in value, prev_ = next_ = nullptr, itpos = AtEnd
	a.DeleteNode(it);
	std::cout << a << "\n";
	it = a.FindFirstElementByValue(375);
	a.DeleteNode(it);
	std::cout << a << "\n";
	
	std::cout << "deleting last:\n";
	List<int>::Iterator i = a.Last(); // int& x = 3; cannot bind non-const lvalue reference of type() to an rvalue of type (), made Iterator& --> Iterator
	a.DeleteNode(i);
	std::cout << a << "\n";
	
	List<int> c;
	c.AddFirst(1);
	c.AddFirst(2);
	std::cout << c << "\n";
	
	List<int>::Iterator it2 = c.Last();
	c.DeleteNode(it2);
	std::cout << c << "\n";
	
	it2 = c.Last();
	c.DeleteNode(it2);
	std::cout << c << "\n";
	
	
	List<char> b;
	b.AddFirst('b');
	b.AddFirst('m');
	List<char>::Iterator it1;
	std::cout << b << "\n";
	it1 = b.FindFirstElementByValue('m'); // trash in value, prev_ = next_ = nullptr, itpos = AtEnd
	b.DeleteNode(it1);
	std::cout << b << "\n";
}

void TestCopyListConstructor() {
	std::cout << "TestCopyListConstructor\n";
	List<int> a;
	a.AddFirst(17);
	a.AddFirst(6);
	std::cout << a << "\n";
	List<int> c = List<int>(a);
	std::cout << c << "\n";
	
	List<char> b;
	b.AddFirst('b');
	b.AddFirst('m');
	std::cout << b << "\n";
	List<char> d(b);
	std::cout << d << "\n";
	
}

void TestListConcatenation() {
	std::cout << "TestCopyListConcatenation\n";
	List<int> a;
	a.AddFirst(17);
	a.AddFirst(6);
	std::cout << "a: " << a << "\n";
	
	List<int> b;
	b.AddFirst(5);
	b.AddFirst(3);
	std::cout << "b: " << b << "\n";
	
	a += b;
	std::cout << "a + b: " << a << "\n";
}

void TestListEqual() {
	std::cout << "TestListEqual\n";
	List<int> a;
	a.AddFirst(17);
	a.AddFirst(6);
	std::cout << "a: " << a << "\n";
	
	List<int> b;
	b.AddFirst(5);
	b.AddFirst(3);
	std::cout << "b: " << b << "\n";
	
	std::cout << (a == b) << "\n";
}

void TestListOfLists() {
	std::cout << "\nTestListOfLists\n";
	List<List<int>> list;
	List<int> a, b, c;
	a.AddLast(1);
	a.AddLast(2);
	
	b.AddLast(1);
	b.AddLast(2);
	b.AddLast(3);

	c.AddLast(1);
	c.AddLast(2);
	c.AddLast(3);
	c.AddLast(4);

	list.AddLast(a);
	list.AddLast(b);
	list.AddLast(c);
	
	
	std::cout << list << "\n";
}

int main(int argc, char** argv) {
	try {
		switch(argc) {
			case 1: {
				std::cout << "-----------------------------------------------------------------\n";
				std::cout << "TestInsertBefore\n";
				std::cout << "TestAddFirst\n";
				std::cout << "TestAddLast\n";
				std::cout << "TestDeleteNode\n";
				std::cout << "TestListConcatenation\n";
				std::cout << "TestCopyListConstructor()\n";
				std::cout << "TestListOfLists\n";
				break;
			}
			case 2: {
				if (strcmp(argv[1], "TestAll") == 0) { // they're equal
					TestAll();
				}
				else if (strcmp(argv[1], "TestInsertBefore") == 0) {
					TestInsertBefore();
				}
				else if (strcmp(argv[1], "TestAddFirst") == 0) {
					TestAddFirst();
				}
				else if (strcmp(argv[1], "TestAddLast") == 0) {
					TestAddLast();
				}
				else if (strcmp(argv[1], "TestDeleteNode") == 0) {
					TestDeleteNode();
				}
				else if (strcmp(argv[1], "TestListConcatenation") == 0) {
					TestListConcatenation();
				}
				else if (strcmp(argv[1], "TestListConcatenation") == 0) {
					TestCopyListConstructor();
				}
				else if (strcmp(argv[1], "TestListOfLists") == 0) {
					TestListOfLists();
				}
				break;
			}
			default :{
				std::cout << "something in switch went wrong\n";
			}
		}
	} catch (Exception &e) {
		std::cout << e << "\n";
	}
	return 0;
}