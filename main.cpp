#include "DHHashTable.h"
#include "QPHashTable.h"
#include <iostream>
#include <fstream>

//PRE: None
//POST: Program complete
//RET: 0
int main(int argc, char** argv)
{
  //setting up list

  //i/o loop
  bool keepRunning = true;
  while(keepRunning){
      std::cout<<"Please choose one of the following commands: \n1- Test HashTables\n2- Performance Comparison\n3- Exit";
      int choice;
      std::cin >> choice;
      switch (choice){
        case 2:{
          int m = 1000000;
          //repeat whole experiment 5 times
          for(int i =0;i <5; i++){
            int allSizesAvg;
            int* sizes = {.1*m, .2*m, .3*m, .4*m, .5*m};
            //try 5 different seeds with 5 different input sizes
            for(int j =0;j<5;j++){
              int currSize = sizes[j];
              int currFindSize = sizes[j]/10;
              int* seeds = {1, 2, 3, 4, 5};

              int dhInsertAvg=1;
              int qpInsertAvg=1;
              int ohInsertAvg=1;

              int dhFindAvg=1;
              int qpFindAvg=1;
              int ohFindAvg=1;

              int dhNotFoundAvg = 1;
              int dhNumFound =0;
              int qpNotFoundAvg = 1;
              int qpNumFound = 0;
              int ohNotFoundAvg = 1;
              int ohNumFound = 0;
              //build the hash tables with 5 different seeds
              for(int k=0; k<5; k++){
                srand(seeds[k]);
                DHHashTable* dh = new DHHashTable(m);
                QPHashTable* qp = new QPHashTable(m);
                HashTable* oh = new HashTable(m);

                int* valsToInsert = new int[currSize];
                for(int l =0;l<currSize;l++){
                  int toInsert = rand() % (5*m + 1 - 1) + 1;
                  valsToInsert[l] = toInsert;
                }

                int preDh = clock();
                for(int l = 0;l<currSize;l++){
                  dh->insert(valsToInsert[l]);
                }
                int postDh = clock()-preDh;
                dhInsertAvg+=postDh;

                int preQp = clock();
                for(int l = 0;l<currSize;l++){
                  qp->insert(valsToInsert[l]);
                }
                int postQp = clock()-preQp;
                qpInsertAvg+=postQp;

                int preOh = clock();
                for(int l = 0;l<currSize;l++){
                  oh->insert(valsToInsert[l]);
                }
                int postOh = clock()-preOh;
                ohInsertAvg+=postOh;

                int* valsToFind = new int[currFindSize];

                for(int l=0;l<currFindSize;l++){
                  int toFind; = rand() % (5*m + 1 - 1) + 1;
                  valsToFind[l] = toFind;
                }

                for(int l =0;l<currFindSize;l++){
                  int preFind = clock();
                  bool found = dh->find(valsToFind[l]);
                  int postFind = clock()-preDhFind;
                  if(found){
                    dhFindAvg+=postFind;
                    dhNumFound++;
                  }
                  else{
                    dhNotFoundAvg+=postFind;
                  }

                  preFind = clock();
                  found = qp->find(valsToFind[l]);
                  postFind = clock()-preFind;
                  if(found){
                    qpFindAvg+=postFind;
                    qpNumFound++;
                  }
                  else{
                    qpNotFoundAvg+=postFind;
                  }

                  preFind = clock();
                  found = oh->find(valsToFind[l]);
                  postFind = clock()-preFind;
                  if(found){
                    ohFindAvg+=postFind;
                    ohNumFound++;
                  }
                  else{
                    ohNotFoundAvg+=postFind;
                  }
                }

              }
              dhInsertAvg/=5;
              qpInsertAvg/=5;
              ohInsertAvg/=5;


              dhFindAvg/=dhNumFound;
              qpFindAvg/=qpNumFound;
              ohFindAvg/=ohNumFound;
            }

          }

        }
      }
    }
    delete(qp);
    delete(dh);
    delete(oh);
	return (0);
}
