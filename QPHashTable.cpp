#include "QPHashTable.h"
#include <iostream>
//PRE: None
//POST: New QPHashTable constructed
//RET: None
QPHashTable::QPHashTable(int buckets){
  this->numBuckets = buckets;
  this-> table = new int[numBuckets];
  this-> isEmpty = new bool[numBuckets];
  this->numElements = 0;
  for(int i =0;i<numBuckets;i++){
    isEmpty[i] = true;
  }
}
//PRE: QPHashTable constructed
//POST: Memory used by QPHashTable freed
//RET: None
QPHashTable::~QPHashTable(){
  delete [] this->table;
  delete [] this->isEmpty;
  table = nullptr;
  isEmpty = nullptr;
}
//PRE: QPHashTable constructed
//POST: X inserted into QPHashTable if valid bucket could be found in maxI attempts
//RET: True if inserted, false if maxI attempts exceeded or x already found.
bool QPHashTable::insert(int x){
  int i = 0;
  //if (find(x)){
    //printf("Find found %d\n", x);
    //return false;
  //}
  while(i<maxI){
    int pos = h_i(x, i);
    if(pos<numBuckets && isEmpty[pos]==true){
      table[pos] = x;
      isEmpty[pos] = false;
      this->numElements += 1;
      return true;
    }
    else if(isEmpty[pos] == false && table[pos] ==x){
      return false;
    }
    i++;
  }
  return false;
}
///PRE: QPHashTable constructed, x inserted
//POST: X removed from table if found
//RET: True if successfully removed, false otherwise
bool QPHashTable::Delete(int x){
  int i = 0;
  while(i<maxI){
    int pos = h_i(x, i);
    if(!isEmpty[pos] && table[pos]==x){
      isEmpty[pos] = true;
      this->numElements-=1;
      return true;
    }
    i++;
  }
  return false;
}
///PRE: QPHashTable constructed, has values inserted
//POST: Status of QPHashTable printed to terminal
//RET: None
void QPHashTable::print(){
  std::cout << "Hash table with quadratic probing: \n";
  for(int i =0;i<numBuckets;i++){
      if(!isEmpty[i]){
        std::cout<< i << ":";
        std::cout<< table[i] << "\n";
    }
  }
}
//PRE: QPHashTable cnostructed, x inserted
//POST: None
//RET: True if QPHashTable contains x, false otherwise

bool QPHashTable::find(int x){
  int i = 0;
  while(i<maxI){
    int pos = h_i(x, i);
    if(!isEmpty[pos] && table[pos]==x){
      return true;
    }
    i++;
  }
  return false;
}

///PRE:None
//POST: None
//RET: The bucket to try inserting x at on hashing attempt i, using quadratic probing
int QPHashTable::h_i(int x, int i){
  int offset = i*i;
  return((x%numBuckets)+offset)%numBuckets;
  //46 - 46%53+0 % 53 = 46 - FAILS
  //
}

//PRE: QPHashTable constructed, number of elements counted in numElements
//POST: None
//RET: the load factor of the hash table
float QPHashTable::getLF(){
  return ((float)numElements/(float)numBuckets);
}

