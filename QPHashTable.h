#ifndef QPHT_H
#define QPHT_H

class QPHashTable{
public:
  //PRE: None
  //POST: QPHashTable initialized
  //RET: New array-backed hash table with quadratic probing and the specified # of buckets.
  QPHashTable(int buckets, int maxI);
  //PRE: QPHashTable initialized
  //POST: QPHashTable destroyed
  //RET: None
  ~QPHashTable();
  //PRE: QPHashTable initialized, has an available bucket for x
  //POST: X inserted into QPHashTable if bucket available
  //RET: True if successfully inserted, false otherwise
  bool insert(int x);
  //PRE: QPHashTable initialized, x present in elements
  //POST: X removed from QPHashTable if present
  //RET: True if successfully deleted, false otherwise
  bool Delete(int x);
  //PRE: QPHashTable initialized, some elements present
  //POST: Elements of QPHashTable buckets that are not empty printed to terminal
  //RET: None
  void print();
  //PRE: QPHashTable initialized
  //POST: None
  //RET: True if x is present, false otherwise
  bool find(int x);
  //PRE: QPHashTable initialized, some elements present
  //POST: None
  //RET: Number of elements in hash table divided by number of buckets total.
  float getLF();
  int maxI = 20;
private:
  int numBuckets;
  int* table;
  bool* isEmpty;
  int h_i(int x, int i);
  int numElements;
};
#endif
