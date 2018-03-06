#include "HashTable.h"
#include "SinglyLinkedList.h"
#include "Node.h"
#include <iostream>
//create specified amount of SinglyLinkedLists to serve as hashtable buckets
HashTable::HashTable(int buckets){
  this->numBuckets = buckets;
  this-> table = new SinglyLinkedList<int>[numBuckets]();
}

HashTable::~HashTable(){
  delete [] this->table;
  table = nullptr;
}
//returns whether insert succeeded
//fails if duplicate as duplicates cannot be added to our SinglyLinkedLists
bool HashTable::insert(int x){
  int targetBucket = hash(x);
  SinglyLinkedList<int>* list = &this->table[targetBucket];
  //most recently added object should be at front of list for quick retrieval
  //added an addFront method to the linkedlist from lab 1 to perform this insert
  return(list->addFront(x));
}
bool HashTable::Delete(int x){
  int targetBucket = hash(x);
  SinglyLinkedList<int>* list = &this->table[targetBucket];
  return list->erase(x);
}
//print each list with its index
void HashTable::print(){
  std::cout<<"Open Hashing:\n";
  for(int i =0;i<numBuckets;i++){
    SinglyLinkedList<int>* list = &this->table[i];
    if(!list->isEmpty()){
      std::cout<< i << ":";    
      list->print();
    }
  }
}
//search each list
bool HashTable::find(int x){
  //get the bucket that the searched object would be in
  SinglyLinkedList<int>* list = &this->table[hash(x)];
  if(list->find(x)!=nullptr){
    return true;
  }
  return false;
}

int HashTable::hash(int x){
  return x%numBuckets;
}
