#include "Node.h"
#include "SinglyLinkedList.h"
#include <iostream>
template <class T>
SinglyLinkedList<T>::SinglyLinkedList(){
  head = nullptr;
}
template <class T>
SinglyLinkedList<T>::~SinglyLinkedList(){
  Node<T>* curr = head;
  Node<T>* prev = nullptr;
  while(curr != nullptr){
    prev = curr;
    curr = curr->next;
    delete(prev);
  }
}
//wrapper for recursive insert function so main.cpp doesn't need to see head
template <class T>
void SinglyLinkedList<T>::insert(T newVal){
  std::cout << "Inserting to sll\n";
  if(head != nullptr){
    std::cout << "Head is: " << head->val;
  }
  recursiveInsert(newVal, nullptr, head);
}
//Insert node recursively, setting head if list is empty. Fails and returns message if item is already in list.
template <class T>
void SinglyLinkedList<T>::recursiveInsert(T newVal, Node<T>* prev, Node<T>* curr){
  if(prev == nullptr && this->find(newVal)){
     std::cout << "Value already exists in list and was not added\n";
     return;
  }
  if(head == nullptr){
    head = new Node<T>(newVal);
  }
  else if(curr==nullptr){
    curr = new Node<T>(newVal);
    prev->next = curr;
  }
  else{
    recursiveInsert(newVal, curr, curr->next);
  }
  size++;
}

template <class T>
bool SinglyLinkedList<T>::addFront(T newVal){
  if (this->find(newVal)){
    return false;
  }
  Node<T>* newNode = new Node<T>(newVal);
  if(head != nullptr){
    newNode->next = head;
  }
  head = newNode;
  size++;
  return true;
}

template <class T>
bool SinglyLinkedList<T>::isEmpty(){
  return (size==0);
}
//Wrapper for recursive method to erase target value
template <class T>
bool SinglyLinkedList<T>::erase(T valToRemove){
  return recursiveErase(valToRemove, head, nullptr);
}
//erase target value recursively and return bool for success/fail
template <class T>
bool SinglyLinkedList<T>::recursiveErase(T valToRemove, Node<T>* curr, Node<T>* prev){
  if (curr==nullptr){
    return false;
  }
  else if (curr->val==valToRemove){
    if (prev != nullptr){
      prev->next=curr->next;
    }
    else{
      head = curr->next;
    }
    size--;
    return true;
  }
  else{
    return recursiveErase(valToRemove, curr->next, curr);
  }
}
//Print all node values
template <class T>
void SinglyLinkedList<T>::print(){
  Node<T>* curr = head;
  while(curr != nullptr){
    std::cout<<curr->val;
    std::cout << " ";
    curr = curr->next;
  }
  std::cout << "\n";
}
//Iteratively find the node with a given value and return it or null if not found
template <class T>
Node<T>* SinglyLinkedList<T>::find(T targetVal){  
  Node<T>* curr = head;
  while(curr != nullptr){
    if(curr->val == targetVal){
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}
template class SinglyLinkedList<int>;
