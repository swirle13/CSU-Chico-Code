/* This assignment originated at UC Riverside. The hash table size
 should be defined at compile time. Use -D HASH_TABLE_SIZE=X */

#ifndef __HASH_H
#define __HASH_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <iterator>

using std::cout;
using std::endl;
using std::list;
using std::string;

class Hash {

public:
   Hash();                          // constructor
   void remove(string);             // remove key from hash table
   void print();                    // print the entire hash table
   void processFile(string);        // open file and add keys to hash table
   bool search(string);             // search for a key in the hash table
   void output(string);             // print entire hash table to a file
   void printStats();               // print statistics

private:
   // HASH_TABLE_SIZE should be defined using the -D option for g++
   list<string> hashTable [HASH_TABLE_SIZE];
   int collisions;                  // total number of collisions
   unsigned int longestList;        // longest list ever generated
   double runningAvgListLength;     // running average of average list length

   int hf(string);                  // the hash function

// put additional functions below as needed
// do not change anything above!
   unsigned int getLongestList(int);// Returns the length of the longest list
                                    // in the hash table
   
   double avgLength();              // Returns the average length of list in 
                                    // hash table slot

   double loadFactor;               // Variable to store the load factor of the 
                                    // hash table
};

#endif
