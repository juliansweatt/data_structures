#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>

namespace cop4530 {

	template <typename T>
		class List {
			private:
				// nested Node class
				struct Node {
					T data;
					Node *prev;
					Node *next;

					Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr)
						: data{d}, prev{p}, next{n} {}
					Node(T && d, Node *p = nullptr, Node *n = nullptr)
						: data{std::move(d)}, prev{p}, next{n} {}
				};

			public:
				//nested const_iterator class
				class const_iterator {// D O N E
					public:
						const_iterator(); // default zero parameter constructor // Done
						const T & operator*() const; // operator*() to return element //done

						// increment/decrement operators
						const_iterator & operator++();//done
						const_iterator operator++(int);//done
						const_iterator & operator--();//done
						const_iterator operator--(int);//done

						// comparison operators
						bool operator==(const const_iterator &rhs) const; //done
						bool operator!=(const const_iterator &rhs) const;//done

					protected:
						Node *current; // pointer to node in List
						T & retrieve() const; // retrieve the element refers to //done
						const_iterator(Node *p); // protected constructor //done

						friend class List<T>;
				};

				// nested iterator class
				class iterator : public const_iterator {//D O N E
					public:
						iterator();//done
						T & operator*();//done
						const T & operator*() const;//done

						// increment/decrement operators
						iterator & operator++();//done
						iterator operator++(int);//done
						iterator & operator--();//done
						iterator operator--(int);//done

					protected:
						iterator(Node *p);//done
						friend class List<T>;
				};

			public:
				// constructor, desctructor, copy constructor
				List(); // default zero parameter constructor//done
				List(const List &rhs); // copy constructor//done
				List(List && rhs); // move constructor//done
				// num elements with value of val
				explicit List(int num, const T& val = T{});//done
				// constructs with elements [start, end)
				List(const_iterator start, const_iterator end);//done

				~List(); // destructor//done

				// copy assignment operator
				const List& operator=(const List &rhs);// done
				// move assignment operator
				List & operator=(List && rhs);// done

				// member functions
				int size() const; // number of elements //done
				bool empty() const; // check if list is empty//done
				void clear(); // delete all elements//done
				void reverse(); // reverse the order of the elements//done

				T &front(); // reference to the first element//done
				const T& front() const;//done
				T &back(); // reference to the last element//done
				const T & back() const;//done

				void push_front(const T & val); // insert to the beginning//done
				void push_front(T && val); // move version of insert//done
				void push_back(const T & val); // insert to the end//done
				void push_back(T && val); // move version of insert//done
				void pop_front(); // delete first element//done
				void pop_back(); // delete last element//done

				void remove(const T &val); // remove all elements with value = val//done

				// print out all elements. ofc is deliminitor
				void print(std::ostream& os, char ofc = ' ') const;//done

				iterator begin(); // iterator to first element//done
				const_iterator begin() const;//done
				iterator end(); // end marker iterator//done
				const_iterator end() const;//done
				iterator insert(iterator itr, const T& val); // insert val ahead of itr//done
				iterator insert(iterator itr, T && val); // move version of insert//done
				iterator erase(iterator itr); // erase one element//done
				iterator erase(iterator start, iterator end); // erase [start, end)//done


			private:
				int theSize; // number of elements
				Node *head; // head node
				Node *tail; // tail node

				void init(); // initialization//done
		};

	// overloading comparison operators
	template <typename T>
		bool operator==(const List<T> & lhs, const List<T> &rhs);//done

	template <typename T>
		bool operator!=(const List<T> & lhs, const List<T> &rhs);//done

	// overloading output operator
	template <typename T>
		std::ostream & operator<<(std::ostream &os, const List<T> &l);//done

	// include the implementation file here
#include "List.hpp"

} // end of namespace 4530

#endif
