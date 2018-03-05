#ifndef DHHT_H
#define DHHT_H

class DHHashTable{
public:
  //PRE: None
  //POST: DHHashTable initialized
  //RET: New array-backed hash table with double hashing and the specified # of buckets.
  DHHashTable(int buckets);
  //PRE: DHHashTable initialized
  //POST: DHHashTable destroyed
  //RET: None
  ~DHHashTable();
  //PRE: DHHashTable initialized, has an available bucket for x
  //POST: X inserted into DHHashTable if bucket available
  //RET: True if successfully inserted, false otherwise
  bool insert(int x);
  //PRE: DHHashTable initialized, x present in elements
  //POST: X removed from DHHashTable if present
  //RET: True if successfully deleted, false otherwise
  bool Delete(int x);
  //PRE: DHHashTable initialized, some elements present
  //POST: Elements of DHHashTable buckets that are not empty printed to terminal
  //RET: None
  void print();
  //PRE: DHHashTable initialized
  //POST: None
  //RET: True if x is present, false otherwise
  bool find(int x);
  //PRE: DHHashTable initialized, some elements present
  //POST: None
  //RET: Number of elements in hash table divided by number of buckets total.
  float getLF();
  int dhFactor;
  const int maxI = 20;
private:
  int numBuckets;
  int* table;
  bool* isEmpty;
  //PRE: DHHashTable initialized
  //POST: None
  //RET: The hash value of x with a given modifier i using double hashing.
  int h_i(int x, int i);
  int numElements;
};
#endif
