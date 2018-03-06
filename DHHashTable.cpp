#include "DHHashTable.h"
#include <iostream>

//PRE: None
//POST: New DHHashTable constructed
//RET: None
DHHashTable::DHHashTable(int buckets){
  this->dhFactor = buckets;
  this-> table = new int[numBuckets];
  this-> isEmpty = new bool[numBuckets];
  this-> numElements = 0;
  this->numBuckets = buckets;
  for(int i =0;i<numBuckets;i++){
    isEmpty[i] = true;
  }
}
//PRE: DHHashTable constructed
//POST: Memory used by DHHashTable freed
//RET: None
DHHashTable::~DHHashTable(){
  delete [] this->isEmpty;
  delete [] this->table;
}

//PRE: DHHashTable constructed
//POST: X inserted into DHHashTable if valid bucket could be found in maxI attempts
//RET: True if inserted, false if maxI attempts exceeded or x already found.
bool DHHashTable::insert(int x){
  std::cout<<"Inserting...";
  int i =0;
  while(i<maxI){
    int pos = h_i(x, i);
    
    if(this->isEmpty[pos]){
      this->table[pos] = x;
      this->isEmpty[pos] = false;
      this->numElements++;
      return true;
    }
    if (!this->isEmpty[pos] && this->table[pos]==x){
      return false;
    }
    i++;
  }
  return false;
}
///PRE: DHHashTable constructed, x inserted
//POST: X removed from table if found
//RET: True if successfully removed, false otherwise
bool DHHashTable::Delete(int x){
  int i =0;
  while(i<maxI){
    int pos = h_i(x, i);
    if(!isEmpty[pos] && table[pos]==x){
      isEmpty[pos] = true;
      numElements--;
      return true;
    }
    i++;
  }
  return false;
}
///PRE: DHHashTable constructed, has values inserted
//POST: Status of DHHashTable printed to terminal
//RET: None
void DHHashTable::print(){
  std::cout << "Hash table with double hashing: \n";
  for(int i =0;i<numBuckets;i++){
    if(!isEmpty[i]){
      std::cout<< i << ":";
      std::cout<<table[i] << "\n";
    }
  }
}
//PRE: DHHashTable cnostructed, x inserted
//POST: None
//RET: True if DHHashTable contains x, false otherwise
bool DHHashTable::find(int x){
  int i =0;
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
//RET: The bucket to try inserting x at on hashing attempt i, using double hashing
int DHHashTable::h_i(int x, int i){
  int hPlus = dhFactor - (x%dhFactor);
  int offset = i*hPlus;
  return ((x%numBuckets) + offset)%numBuckets;
}
//H^+ = p-(x mod p)
//PRE: DHHashTable constructed, number of elements counted in numElements
//POST: None
//RET: the load factor of the hash table
float DHHashTable::getLF(){
  return ((float)numElements/(float)numBuckets);
}
