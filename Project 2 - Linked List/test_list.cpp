#include <iostream>
#include <string>
#include "List.h"

using namespace std;
using namespace cop4530;

int main() {
	// typedef List<int>::iterator ITRINT;
	// typedef List<string>::iterator ITRSTR;
	List<int> l1;
	// ITRINT itr;
	List<string> l2;
	// ITRSTR itr2;
	const int num = 10;

	cout << "Testing list with integer values ..." << endl;
	cout << "pushing back " << num << " integer values" << endl;

	for (int i = 0; i < num; ++i) {
		l1.push_back(i);
	}
	cout << "size " << l1.size() << endl;

	auto itr = l1.begin();
	cout << *itr++;
	for (; itr != l1.end(); ++itr) {
		cout << " " << *itr;
	}
	cout << endl;

	cout << "pushing front " << num << " integer values" << endl;

	for (int i = 0; i < num; ++i) {
		l1.push_front(i);
	}

	cout << "size " << l1.size() << endl;

	itr = l1.begin();
	cout << *itr++;
	for (; itr != l1.end(); ++itr) {
		cout << " " << *itr;
	}
	cout << endl;

	cout << "pop front " << num/2 << " integer values" << endl;
	for (int i = 0; i < num/2; ++i) {
		l1.pop_front();
	}

	cout << "size " << l1.size() << endl;

	itr = l1.begin();
	cout << *itr++;
	for (; itr != l1.end(); ++itr) {
		cout << " " << *itr;
	}
	cout << endl;

	cout << "pop back " << num/2 << " integer values" << endl;
	for (int i = 0; i < num/2; ++i) {
		l1.pop_back();
	}

	cout << "size " << l1.size() << endl;

	itr = l1.begin();
	cout << *itr++;
	for (; itr != l1.end(); ++itr) {
		cout << " " << *itr;
	}
	cout << endl;

	cout << "removing 0" << endl;
	l1.remove(0);
	cout << "size " << l1.size() << endl;
	cout << l1 << endl;

	cout << "removing first 4 elements" << endl;
	itr = l1.begin();
	auto itr_t = itr;
	for (int i = 0; i < 4; ++i)
		++itr_t;
	l1.erase(itr, itr_t);
	cout << "size " << l1.size() << endl;
	cout << l1 << endl;

	cout << "reverse list" << endl;
	l1.reverse();
	cout << "size " << l1.size() << endl;
	cout << l1 << endl;

	cout << "clearing list" << endl;
	l1.clear();

	if (l1.empty()) {
		cout << "all cleared" << endl;
	} else {
		cout << "wrong with clear() function" << endl;
	}

	cout << "testing other constructors" << endl;
	List<int> l_t1(8, 5);
	List<int> l_t2(l_t1.begin(), l_t1.end());

	cout << l_t2 << endl;

	cout << "testing comparison operators" << endl;
	if (l_t1 == l_t2) {
		cout << "they are the same" << endl;
	} else {
		cout << "wrong" << endl;
	}

	cout << "remove one element from l_t1" << endl;
	l_t1.pop_back();
	if (l_t1 == l_t2) {
		cout << "wronng" << endl;
	} else {
		cout << "they contain different values" << endl;
	}

	l_t2.push_back(10);
	// testing move
	List<int> l_t3 = std::move(l_t2);
	for (auto & x : l_t3) {
		cout << x << " ";
	}
	cout << endl;

	// check if l_t2 is empty now
	// NOTE that we should NOT access l_t2
	// this is just for the purpose of testing
	// the implementation of move constructor
	if (!l_t2.empty()) {
		cout << "wrong" << endl;
	} else {
		cout << "l_t2 is empty now" << endl;
	}

	/* testing string list */
	cout << "Testing list with string values ..." << endl;
	cout << "pushing back " << num << " string values" << endl;

	for (int i = 1; i <= num; ++i) {
		string str(i, '0');
		l2.push_back(str);
	}
	cout << "size " << l2.size() << endl;

	auto itr2 = l2.begin();
	cout << *itr2++;
	for (; itr2 != l2.end(); ++itr2) {
		cout << " " << *itr2;
	}
	cout << endl;

	cout << "pushing front " << num << " integer values" << endl;

	for (int i = 1; i <= num; ++i) {
		string str(i, '1');
		l2.push_front(str);
	}

	cout << "size " << l2.size() << endl;

	itr2 = l2.begin();
	cout << *itr2++;
	for (; itr2 != l2.end(); ++itr2) {
		cout << " " << *itr2;
	}
	cout << endl;

	cout << "pop front " << num/2 << " string values" << endl;
	for (int i = 0; i < num/2; ++i) {
		l2.pop_front();
	}

	cout << "size " << l2.size() << endl;

	itr2 = l2.begin();
	cout << *itr2++;
	for (; itr2 != l2.end(); ++itr2) {
		cout << " " << *itr2;
	}
	cout << endl;

	cout << "pop back " << num/2 << " string values" << endl;
	for (int i = 0; i < num/2; ++i) {
		l2.pop_back();
	}

	cout << "size " << l2.size() << endl;

	itr2 = l2.begin();
	cout << *itr2++;
	for (; itr2 != l2.end(); ++itr2) {
		cout << " " << *itr2;
	}
	cout << endl;

	cout << "removing 0" << endl;
	l2.remove("0");
	cout << "size " << l2.size() << endl;
	cout << l2 << endl;

	cout << "removing first 4 elements" << endl;
	itr2 = l2.begin();
	auto itr2_t = itr2;
	for (int i = 0; i < 4; ++i)
		++itr2_t;
	l2.erase(itr2, itr2_t);
	cout << "size " << l2.size() << endl;
	cout << l2 << endl;

	cout << "reverse list" << endl;
	l2.reverse();
	cout << "size " << l2.size() << endl;
	cout << l2 << endl;

	cout << "clearing list" << endl;
	l2.clear();

	if (l2.empty()) {
		cout << "all cleared" << endl;
	} else {
		cout << "wrong with clear() function" << endl;
	}

	cout << "testing other constructors" << endl;
	List<string> l2_t1(8, "2");
	List<string> l2_t2(l2_t1.begin(), l2_t1.end());

	cout << l2_t2 << endl;

	cout << "testing comparison operators" << endl;
	if (l2_t1 == l2_t2) {
		cout << "they are the same" << endl;
	} else {
		cout << "wrong" << endl;
	}

	cout << "remove one element from l2_t1" << endl;
	l2_t1.pop_back();
	if (l2_t1 == l2_t2) {
		cout << "wronng" << endl;
	} else {
		cout << "they contain different values" << endl;
	}


}
