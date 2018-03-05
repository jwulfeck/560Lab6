#ifndef HT_H
#define HT_H

#include "SinglyLinkedList.h"
//Simple node class with value and next pointer
class HashTable{
public:
  HashTable(int buckets);
  ~HashTable();
  bool insert(int x);
  bool Delete(int x);
  void print();
  bool find(int x);
private:
  int numBuckets;
  SinglyLinkedList<int>* table;
  int hash(int x);
};
#endif
