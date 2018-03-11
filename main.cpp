#include "DHHashTable.h"
#include "QPHashTable.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <iomanip>

template<typename T> void printElement(T t, int width)
{
  //method for printing well-formatted tables at the end
  //from Cyril Leroux on stackoverflow
    const char separator    = ' ';  
    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
}
//PRE: None
//POST: Program complete
//RET: 0
int main(int argc, char** argv)
{
  //setting up list

  //i/o loop
  bool keepRunning = true;
  while(keepRunning){
      std::cout<<"Please choose one of the following commands: \n1- Test HashTables\n2- Performance Comparison\n3- Exit\n";
      int choice;
      std::cin >> choice;
      const int m = 1000003;      
      switch (choice){
        case 1:{
          int size;
          std::cout<<"What is the table size?";
          std::cin >> size;
          DHHashTable* dh = new DHHashTable(size, 5, 4);
          QPHashTable* qp = new QPHashTable(size,4);
          HashTable* oh = new HashTable(size);
          std::ifstream file;
          file.open("data.txt");
          int curr;
          while(file>>curr){
              dh->insert(curr);
              qp->insert(curr);
              oh->insert(curr);
          }
          oh->print();    
          qp->print();          
          dh->print();
          delete(oh);
          delete(qp);
          delete(dh);
          break;
        }
        case 2:{
          float dhBuildAvgs[5] = {0, 0, 0, 0, 0};
          float dhFoundAvgs[5] = {0, 0, 0, 0, 0};
          float dhNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          float dhNumsFound[5] = {0, 0, 0, 0, 0};
          float dhNumsNotFound[5] = {0, 0, 0, 0, 0};

          float qpBuildAvgs[5] = {0, 0, 0, 0, 0};
          float qpFoundAvgs[5] = {0, 0, 0, 0, 0};
          float qpNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          float qpNumsFound[5] = {0, 0, 0, 0, 0};
          float qpNumsNotFound[5] = {0, 0, 0, 0, 0};

          float ohBuildAvgs[5] = {0, 0, 0, 0, 0};
          float ohFoundAvgs[5] = {0, 0, 0, 0, 0};
          float ohNotFoundAvgs[5] = {0, 0, 0, 0, 0};
          float ohNumsFound[5] = {0, 0, 0, 0, 0};
          float ohNumsNotFound[5] = {0, 0, 0, 0, 0};
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
                DHHashTable* dh = new DHHashTable(m, 997,20);
                QPHashTable* qp = new QPHashTable(m,20);
                HashTable* oh = new HashTable(m);

                int* valsToInsert = new int[currSize];


                for(int l =0;l<currSize;l++){
                  int toInsert = rand() % (5*m + 1 - 1) + 1;
                  valsToInsert[l] = toInsert;
                }
                //insert currSize random values into each hash table and accumulate the amount of time taken
                for(int l =0;l<currSize;l++){
                  int pre = clock();
                  dh->insert(valsToInsert[l]);
                  dhBuildAvgs[j]+=(clock()-pre);   

                  pre = clock();
                  qp->insert(valsToInsert[l]);
                  qpBuildAvgs[j]+=(clock()-pre);            

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
                  float preFind = clock();
                  bool found = dh->find(valsToFind[l]);
                  float postFind = clock()-preFind;
                  
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
                  //std::cout<<postFind<<"\n";
                  
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
          int msDiv = CLOCKS_PER_SEC/1000;
          //i represents size
          //each size is run 5 per seed with 5 diff seeds, so 25 builds total are added to each size's avg
          //each size tracks its founds/not founds, so divide total time spent finding/failing to find for each side by those
          for(int i =0;i<5;i++){
            dhBuildAvgs[i] =dhBuildAvgs[i]/(25*msDiv);
            qpBuildAvgs[i] =qpBuildAvgs[i]/(25*msDiv);
            ohBuildAvgs[i] =ohBuildAvgs[i]/(25*msDiv);

            dhFoundAvgs[i] =dhFoundAvgs[i]/(dhNumsFound[i]*msDiv);
            dhNotFoundAvgs[i] = dhNotFoundAvgs[i]/(dhNumsNotFound[i]*msDiv);

            qpFoundAvgs[i] = qpFoundAvgs[i]/(qpNumsFound[i]*msDiv);
            qpNotFoundAvgs[i] =qpNotFoundAvgs[i]/(qpNumsNotFound[i]*msDiv);

            ohFoundAvgs[i] = ohFoundAvgs[i]/(ohNumsFound[i]*msDiv);
            ohNotFoundAvgs[i] =ohNotFoundAvgs[i]/(ohNumsNotFound[i]*msDiv);
          }
        std::cout<<"Performance (Open Hashing):\n";
        printElement("     ",15);
        printElement("100,000",13);
        printElement("200,000",13);
        printElement("300,000",13);
        printElement("400,000",13);
        printElement("500,000",13);
        std::cout << "\n";
        printElement("Build",15);
        printElement(ohBuildAvgs[0],13);
        printElement(ohBuildAvgs[1],13);
        printElement(ohBuildAvgs[2],13);
        printElement(ohBuildAvgs[3],13);
        printElement(ohBuildAvgs[4],13);
        std::cout << "\n";
        printElement("Found",15);
        printElement(ohFoundAvgs[0],13);
        printElement(ohFoundAvgs[1],13);
        printElement(ohFoundAvgs[2],13);
        printElement(ohFoundAvgs[3],13);
        printElement(ohFoundAvgs[4],13);
        std::cout << "\n";
        printElement("Not Found",15);
        printElement(ohNotFoundAvgs[0],13);
        printElement(ohNotFoundAvgs[1],13);
        printElement(ohNotFoundAvgs[2],13);
        printElement(ohNotFoundAvgs[3],13);
        printElement(ohNotFoundAvgs[4],13);
        
        std::cout<<"\n";        
        std::cout<<"Performance (Quadratic Probing):\n";
        printElement("     ",15);
        printElement("100,000",13);
        printElement("200,000",13);
        printElement("300,000",13);
        printElement("400,000",13);
        printElement("500,000",13);
        std::cout << "\n";
        printElement("Build",15);
        printElement(qpBuildAvgs[0],13);
        printElement(qpBuildAvgs[1],13);
        printElement(qpBuildAvgs[2],13);
        printElement(qpBuildAvgs[3],13);
        printElement(qpBuildAvgs[4],13);
        std::cout << "\n";
        printElement("Found",15);
        printElement(qpFoundAvgs[0],13);
        printElement(qpFoundAvgs[1],13);
        printElement(qpFoundAvgs[2],13);
        printElement(qpFoundAvgs[3],13);
        printElement(qpFoundAvgs[4],13);
        std::cout << "\n";
        printElement("Not Found",15);
        printElement(qpNotFoundAvgs[0],13);
        printElement(qpNotFoundAvgs[1],13);
        printElement(qpNotFoundAvgs[2],13);
        printElement(qpNotFoundAvgs[3],13);
        printElement(qpNotFoundAvgs[4],13);

        std::cout<<"\n";
        std::cout<<"Performance (Double Hashing):\n";
        printElement("     ",15);
        printElement("100,000",13);
        printElement("200,000",13);
        printElement("300,000",13);
        printElement("400,000",13);
        printElement("500,000",13);
        std::cout << "\n";
        printElement("Build",15);
        printElement(dhBuildAvgs[0],13);
        printElement(dhBuildAvgs[1],13);
        printElement(dhBuildAvgs[2],13);
        printElement(dhBuildAvgs[3],13);
        printElement(dhBuildAvgs[4],13);
        std::cout << "\n";
        printElement("Found",15);
        printElement(dhFoundAvgs[0],13);
        printElement(dhFoundAvgs[1],13);
        printElement(dhFoundAvgs[2],13);
        printElement(dhFoundAvgs[3],13);
        printElement(dhFoundAvgs[4],13);
        std::cout << "\n";
        printElement("Not Found",15);
        printElement(dhNotFoundAvgs[0],13);
        printElement(dhNotFoundAvgs[1],13);
        printElement(dhNotFoundAvgs[2],13);
        printElement(dhNotFoundAvgs[3],13);
        printElement(dhNotFoundAvgs[4],13);
        std::cout << "\n";
        std::cout << "All times in millseconds.\n";
        break;
        
        }
        case 3:
        {
          keepRunning = false;
          break;
        }
      }
    }

	return (0);
}

