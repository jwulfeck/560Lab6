#ifndef SLL_H
#define SLL_H
#include "Node.h"
template<class T>
class SinglyLinkedList{
public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void insert(T newVal);
  void recursiveInsert(T newVal, Node<T>* prev, Node<T>* curr);
  bool addFront(T newVal);
  bool isEmpty();
  bool erase(T valToRemove);
  bool recursiveErase(T valToRemove, Node<T>* head, Node<T>* prev); //should delete last one
  void print();
  Node<T>* find(T targetVal);
private:
  Node<T>* head = nullptr;
  int size = 0;
};
#endif
