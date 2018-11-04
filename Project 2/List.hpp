// ========== Begin ========== //

// ---------- Overloads ---------- //
template<typename T>                            // Overload: Copy Assignment
const List<T> & List<T>::operator=(const List<T> & rhs)
{
  auto copy = rhs;
  std::swap(*this, copy);
  return *this;
}

template<typename T>
List<T> & List<T>::operator=(List<T> && rhs)    // Move Assignment
{
  init();
  *this = std::move(rhs);
  return *this;
}

template<typename T>                            // Returns un-modifiable reference to corresponding element in the list
const T & List<T>::const_iterator::operator*() const
{
  return retrieve();
}

template<typename T>
T & List<T>::iterator::operator*()
{
  return this->current->data;
}

template<typename T>
const T & List<T>::iterator::operator*() const  // Returns reference to corresponding element in the list
{
  return this->retrieve();
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++()
{
  current = current->next;
  return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  auto old = *this;
  ++(*this);
  return old;
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--()
{
  current = current->prev;
  return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  auto old = *this;
  --(*this);
  return *this;
}

template<typename T>
bool List<T>::const_iterator::operator==(const typename List<T>::const_iterator & rhs) const
{
  return current == rhs.current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const typename List<T>::const_iterator & rhs) const
{
  return current != rhs.current;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
  this->current = this->current->next;
  return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  iterator old = *this;
  ++( *this );
  return old;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
  this->current = this->current->prev;
  return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  auto old = *this;
  --(*this);
  return *this;
}

// ---------- Global Overloads ---------- //

template <typename T>   // Equivalency operator overload (compares two whole lists). Depends on iterators.
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
  bool answer = true;
  if(lhs.size() == rhs.size())
  {
    auto itrRhs = rhs.begin();
    for(auto itrLhs = lhs.begin(); itrLhs != lhs.end() ;itrLhs++)
    {
      if(*itrLhs != *itrRhs)  // If any element in lhs doesnt match rhs, break loop and return false
      {
        answer = false;
        break;
      }
      itrRhs++;
    }
    return answer;
  }
  else    // Lists are assumed to be non-equal if their sizes are different
    return false;
}

template<typename T>    // Non-Equivalency Operator Overload. Depends on operator== overload (above)
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
  return !(rhs == lhs);
}

template<typename T>    // Print out all elements in list l by calling List<T>::print() function.
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
  l.print(os);
  return os;
}

// ---------- Constructors ---------- //
template<typename T>    // No Parameter const_iterator Constructor
List<T>::const_iterator::const_iterator() : current{nullptr}
{

}

template<typename T>    // Parameter const_iterator Constructor (Protected)
List<T>::const_iterator::const_iterator( typename List<T>::Node* p ) : current{p}
{

}

template<typename T>    // No Parameter iterator Constructor
List<T>::iterator::iterator()
{

}

template<typename T>    // Parameter iterator Cosntructor
List<T>::iterator::iterator(typename List<T>::Node* p) : List<T>::const_iterator{p}
{

}

template<typename T>    // No Parameter Constructor
List<T>::List()
{
  init();
}

template<typename T>    // Copy Constructor
List<T>::List(const List<T> & rhs)
{
  init();
  for(auto & x : rhs)
    push_back( x );
}

template<typename T>    // Move Constructor
List<T>::List(List<T> && rhs) : theSize(rhs.theSize), head{rhs.head}, tail{rhs.tail}
{
  rhs.theSize = 0;
  rhs.head = nullptr;
  rhs.tail = nullptr;
}

template<typename T>    // Constructor: Int only (no auto type conversion). (size (int), fillValue(any type))
List<T>::List(int num, const T &val)
{
  init();
  for(int i = 0; i < num; i++)
    push_back(val);
}

template<typename T>    // Constructor: Create a new List from an existing one from elements [start, end)
List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end)
{
  init();
  for(auto itr = start; itr != end; ++itr)
    push_back(*itr);
}

template<typename T>    // Destructor
List<T>::~List()
{
	clear();
	delete head;
	delete tail;
}

// ---------- Mutators ---------- //
template<typename T>
void List<T>::clear( )
{
    while( !empty( ) )
        pop_front( );
}

template<typename T>
void List<T>::init()
{
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}

template<typename T>
void List<T>::push_front( const T &x)
{
  insert(begin(),x);
}

template<typename T>
void List<T>::push_front( T && x)
{
  insert(begin(), std::move(x));
}

template<typename T>
void List<T>::push_back(const T & x)
{
  insert(end(), x);
}

template<typename T>
void List<T>::push_back(T && x)
{
  insert(end(),std::move(x));
}

template<typename T>
void List<T>::pop_front()
{
  erase(begin());
}

template<typename T>
void List<T>::pop_back()
{
  erase(--end());
}

template<typename T>
void List<T>::reverse()
{
  if(!empty())
  {
    auto itr = head;
    while(itr != nullptr)
    {
      std::swap(itr->next, itr->prev);
      itr = itr->prev;
    }
  }
  std::swap(head,tail); // Necessary to prevent segFaults (Ensure the tail's next [instead of prev] element is nullptr)
}

template<typename T>
void List<T>::remove(const T & val)
{
  for(auto itr = begin(); itr != end(); itr++)
  {
    if(*itr == val)
      erase(itr);
  }
}

// ---------- Accessors ---------- //

template<typename T>
int List<T>::size() const
{
  return theSize;
}

template<typename T>
bool List<T>::empty() const
{
  return size() == 0;
}

template<typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
  for( auto itr = begin(); itr != end(); ++itr)
    os << *itr << ofc;
}

template<typename T>    // reference to the first element (modifiable)
T & List<T>::front()
{
  return *begin();
}

template<typename T>    // reference to the first element (not modifiable)
const T& List<T>::front() const
{
  return *begin();
}

template<typename T>    // reference to the last element (modifiable)
T & List<T>::back(){
  return *(--end());    // Returns --end() because end() is actually the element after the final element (out of bounds)
}

template<typename T>    // reference to the last element (not modifiable)
const T & List<T>::back() const
{
  return *(--end());
}

// ========== Iterator Functions ========== //
// ---------- Iterator Mutators ---------- //
template<typename T>    // Constant Insert
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T & x)
{
  auto *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
}

template<typename T>    // Non Constant Insert (Move)
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, T &&x)
{
  auto *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr)
{
  auto *p = itr.current;
  typename List<T>::iterator retVal{p->next};
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  theSize--;
  return retVal;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator from, typename List<T>::iterator to)
{
  for(auto itr = from; itr != to;)
    itr = erase(itr);
  return to;
}

// ---------- Iterator Accessors ---------- //
template<typename T>
typename List<T>::iterator List<T>::begin()
{
  return { head->next };
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
  return{ head->next };
}

template<typename T>
typename List<T>::iterator List<T>::end()
{
  return tail;
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
  return tail;
}

template<typename T>
T & List<T>::const_iterator::retrieve() const
{
  return current->data;
}

// ========== End ========== //
