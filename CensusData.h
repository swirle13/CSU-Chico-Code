/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger and Troy Jones
 * @date 2/22/13
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!
//
   // insertion sort helpers
   void insertionSortByName(vector<Record*>&);
   void insertionSortByPop(vector<Record*>&);

   // merge sort helpers
   void mergeSortByName(vector<Record*>&, int, int);  // divide functions
   void mergeSortByPop(vector<Record*>&, int, int);   
   void mergeName(vector<Record*>&, int, int, int);   // conquer functions
   void mergePop(vector<Record*>&, int, int, int);    

   // quick sort helpers
   void quickSortByPop(vector<Record*>&, int, int);   // divide functions
   void quickSortByName(vector<Record*>&, int, int);
   int popPartion(vector<Record*>&, int, int);        // conquer functions
   int namePartion(vector<Record*>&, int, int);
};

#endif // CSCI_311_CENSUSDATA_H