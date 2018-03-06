#include "DHHashTable.h"
#include "QPHashTable.h"
#include "HashTable.h"
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
      int m = 1000000;      
      switch (choice){
        case 1:{

          DHHashTable* dh = new DHHashTable(m);
          QPHashTable* qp = new QPHashTable(m);
          HashTable* oh = new HashTable(m);
          std::ifstream file;
          file.open("data.txt");
          int curr;
          while(file>>curr){
              dh->insert(curr);
              qp->insert(curr);
              oh->insert(curr);
          }
        }
        case 2:{
          int dhBuildAvgs[5] = {0, 0, 0, 0, 0};
          int dhFoundAvgs[5] = {0, 0, 0, 0, 0};
          int dhNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          int dhNumsFound[5] = {0, 0, 0, 0, 0};
          int dhNumsNotFound[5] = {0, 0, 0, 0, 0};

          int qpBuildAvgs[5] = {0, 0, 0, 0, 0};
          int qpFoundAvgs[5] = {0, 0, 0, 0, 0};
          int qpNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          int qpNumsFound[5] = {0, 0, 0, 0, 0};
          int qpNumsNotFound[5] = {0, 0, 0, 0, 0};

          int ohBuildAvgs[5] = {0, 0, 0, 0, 0};
          int ohFoundAvgs[5] = {0, 0, 0, 0, 0};
          int ohNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          int ohNumsFound[5] = {0, 0, 0, 0, 0};
          int ohNumsNotFound[5] = {0, 0, 0, 0, 0};
          //repeat whole experiment 5 times
          for(int i =0;i <5; i++){
            int sizes[5] = {100000, 200000, 300000, 400000, 500000};

            //5 different input sizes
            for(int j =0;j<5;j++){
              int currSize = sizes[j];
              int currFindSize = sizes[j]/10;
              int seeds[5] = {1, 2, 3, 4, 5};


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
                //insert currSize random values into each hash table and accumulate the amount of time taken
                for(int l =0;l<currSize;l++){
                  std::cout << "inserting";
                  std::cout << " " << valsToInsert[l] << "to dh.\n";
                  int pre = clock();
                  dh->insert(valsToInsert[l]);
                  dhBuildAvgs[j]+=(clock()-pre);   

                  std::cout << "inserting";
                  std::cout << " " << valsToInsert[l] << "to qp.\n";
                  pre = clock();
                  qp->insert(valsToInsert[l]);
                  qpBuildAvgs[j]+=(clock()-pre);            

                  std::cout << "inserting";
                  std::cout << " " << valsToInsert[l] << "to oh.\n";
                  pre = clock();
                  oh->insert(valsToInsert[l]);
                  ohBuildAvgs[j]+=(clock()-pre);
                }

                int* valsToFind = new int[currFindSize];

                for(int l=0;l<currFindSize;l++){
                  int toFind = rand() % (5*m + 1 - 1) + 1;
                  valsToFind[l] = toFind;
                }

                for(int l =0;l<currFindSize;l++){
                  int preFind = clock();
                  bool found = dh->find(valsToFind[l]);
                  int postFind = clock()-preFind;
                  if(found){
                    dhFoundAvgs[j]+=postFind;
                    dhNumsFound[j]++;
                  }
                  else{
                    dhNotFoundAvgs[j]+=postFind;
                    dhNumsNotFound[j]++;
                  }

                  preFind = clock();
                  found = qp->find(valsToFind[l]);
                  postFind = clock()-preFind;
                  if(found){
                    qpFoundAvgs[j]+=postFind;
                    qpNumsFound[j]++;
                  }
                  else{
                    qpNotFoundAvgs[j]+=postFind;
                    qpNumsNotFound[j]++;
                  }

                  preFind = clock();
                  found = oh->find(valsToFind[l]);
                  postFind = clock()-preFind;
                  if(found){
                    ohFoundAvgs[j]+=postFind;
                    ohNumsFound[j]++;
                  }
                  else{
                    ohNotFoundAvgs[j]+=postFind;
                    ohNumsNotFound[j]++;
                  }
                }
                delete(qp);
                delete(dh);
                delete(oh);
              }
            }

          }
          //i represents size
          //each size is run 5 per seed with 5 diff seeds, so 25 builds total are added to each size's avg
          //each size tracks its founds/not founds, so divide total time spent finding/failing to find for each side by those
          for(int i =0;i<5;i++){
            dhBuildAvgs[i]/=25;
            qpBuildAvgs[i]/=25;
            ohBuildAvgs[i]/=25;

            dhFoundAvgs[i]/=dhNumsFound[i];
            dhNotFoundAvgs[i]/=dhNumsNotFound[i];

            qpFoundAvgs[i]/=qpNumsFound[i];
            qpNotFoundAvgs[i]/=qpNumsNotFound[i];

            ohFoundAvgs[i]/=ohNumsFound[i];
            ohNotFoundAvgs[i]/=ohNotFoundAvgs[i];
          }

        }
      }
    }

	return (0);
}