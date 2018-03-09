#include "Node.h"
//node constructor
template <class T>
Node<T>::Node(T initVal){
  val = initVal;
  next = nullptr;
}
template class Node<int>;
