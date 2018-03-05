#ifndef NODE_H
#define NODE_H
//Simple node class with value and next pointer
template <class T>
class Node{
public:
  Node(T initVal);
  T val;
  Node* next;
};
#endif
