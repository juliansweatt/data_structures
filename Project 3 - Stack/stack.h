#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>

namespace cop4530
{
  template <typename T>
	class Stack
  {
  protected:
    std::vector<T> data;
  public:
    Stack();//?
    ~Stack();//
    Stack(const Stack<T>&);//?                        //Copy Constructor
    Stack(Stack<T> &&);//?                            //Move Constructor
    Stack<T>& operator=(const Stack <T>&);//?         //Copy Assignment Operator=
    Stack<T>& operator=(Stack<T>&&);//?               //Move Assignment Operator=
    bool empty() const;//                            //True if empty, else false
    void clear();//                                  //Delete all elements
    void push(const T& x);//                         //Add x to stack (Copy)
    void push(T && x);//                             //Add x to stack (Move)
    void pop();//                                    //Remove and disgard top element
    T& top();//                                      //Mutator: Returns reference to top element
    const T& top() const;//                          //Accessor: Returns top element
    int size() const;//                              //Returns number of elements
    void print(std::ostream& os, char ofc = ' ') const;//  //Print to os, ofc is the seperator (oldest to newest elements printed)

  };

  template<typename T>
  std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

  template<typename T>
  bool operator== (const Stack<T>&, const Stack <T>&);

  template<typename T>
  bool operator!= (const Stack<T>&, const Stack <T>&);

  template<typename T>
  bool operator<=(const Stack<T>& a, const Stack <T>& b);

  #include "stack.hpp"
}
#endif
