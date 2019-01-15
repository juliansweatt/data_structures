using namespace std;

template<typename T>    // No Parameter Constructor
Stack<T>::Stack()
{

}

template<typename T>
Stack<T>::~Stack()
{
  clear();
}

template<typename T>
bool Stack<T>::empty() const
{
  return data.size() == 0;
}

template<typename T>
void Stack<T>::clear()
{
  data.clear();
}

template<typename T>
void Stack<T>::push(const T& x)
{
  data.push_back(x);
}

template<typename T>
void Stack<T>::push(T && x)
{
  data.push_back(move(x));
}

template<typename T>
void Stack<T>::pop()
{
  if(data.size() != 0)
    data.pop_back();
}

template<typename T>
int Stack<T>::size() const
{
  return data.size();
}

template<typename T>
T& Stack<T>::top()
{
    return data.back();
}

template<typename T>
const T& Stack<T>::top() const
{
  return data.back();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& src) //??
{
  data = src.data;
}

template<typename T>
Stack<T>::Stack(Stack<T> && src)
{
  data = move(src.data);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack <T>& src)
{
  if(*this != src)
  {
    data = src.data;
  }
  return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& src)
{
  data = move(src.data);
  return *this;
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
  for(int i = 0; i < data.size(); i++)
  {
    os << data[i] << ofc;
  }
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
  a.print(os);
  return os;
}

template<typename T>
bool operator== (const Stack<T>&a, const Stack <T>&b)
{
  bool flag = true;

  if(b.size() != a.size())
    return false;
  else
  {
    bool flag = true;
    Stack<T> a_i;
    Stack<T> b_i;
    a_i = a;
    b_i = b;
    while(flag && !(b_i.empty()))
    {
      if(a_i.top()!=b_i.top())
      {
        bool flag = false;
        break;
      }
      a_i.pop();
      b_i.pop();
    }
  return flag;
  }
}

template<typename T>
bool operator!= (const Stack<T>&a, const Stack <T>&b)
{
  return !(a == b);
}

template<typename T>
bool operator<=(const Stack<T>& a, const Stack <T>& b)
{/*
  bool flag = true;

  if(b.size() != a.size())
    return false;
  else
  {
    for(int i = 0; i < a.size(); i++)
    {
      if((a[i]!=a[b])||(a[i]>b[i]))
      {
        flag = false;
        break;
      }
    }
    return flag;
  }*/

  bool flag = true;

  if(b.size() < a.size())
    return false;
  else
  {
    bool flag = true;
    Stack<T> a_i;
    Stack<T> b_i;
    a_i = a;
    b_i = b;
    /*
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "a_i: " << a_i << endl;
    cout << "b_i: " << b_i << endl;
    */
    while(flag && !(b_i.empty()))
    {
      if(a_i.top()<=b_i.top())
      {
        // Do nothing
      }
      else
      {
        flag = false;
        break;
      }
      a_i.pop();
      b_i.pop();
    }
  return flag;
  }
}
