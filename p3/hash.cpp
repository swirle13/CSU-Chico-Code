/**
 * @file    hash.cpp
 * 
 * @brief   Functions that pertain to hash.h
 * 
 * @author  Troy Jones
 * @date    3/30/17
 */
#include "hash.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


/**
 * Hash()
 *
 * Constructor that initializes member variables.
 */
Hash::Hash()
{
    collisions = 0;
    loadFactor = 0;
    longestList = 0;
    runningAvgListLength = 0.0;
}


/**
 * avgLength()
 *
 * Function that determines the average length of each list if there are
 * collisions present.
 */
double Hash::avgLength()
{
    double newAverage = 0;
    double notEmptyList = 0;
    double sumOfLists = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        // if slot is not empty, increment number of not empty slots.
        if (!hashTable[i].empty())
        {
            ++notEmptyList;     
        }                       
    }
    if(notEmptyList != 0)   // if there are not empty slots
    {
        // add up the length of every list
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            sumOfLists += hashTable[i].size();
        }
        // divide the sum by the number of not empty slots to get average
        newAverage = sumOfLists / notEmptyList;
    }
    return newAverage;
}


/**
 * output()
 *
 * Prints to the output file passesd in by the user.
 *
 * @params filename    The name of the output file.
 */
void Hash::output(string filename)
{
    std::ofstream output;
    output.open(filename);
    if (output.is_open())
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            output << i << ":\t";
            list<string>::iterator iter;
            for (iter = hashTable[i].begin(); iter != hashTable[i].end();
                 iter++)
            {
                output << *iter << ", ";
            }
            output << endl;
        }
        output.close();
    }
}


/**
 * print()
 *
 * Prints hash table and calculates load factor
 */
void Hash::print()
{

    if(hashTable)
    {
        double numOfElements = 0;
        double numOfSlots = 0;
        string str = "";

        for (unsigned int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            cout << i << ":\t";
            str = "";
            ++numOfSlots;    // increments number of total slots

            if (!hashTable[i].empty())  // if slot is not empty
            {
                std::list<string>::iterator iter = hashTable[i].begin();
                while (iter != hashTable[i].end())
                {
                    cout << *iter << ", ";
                    ++iter;
                    ++numOfElements;    // increments number of items
                }
                cout << endl;
            }
            else    // if slot is empty
            {
                cout << str << endl;
            }
            loadFactor = numOfElements / numOfSlots;
        }
    }
}


/**
 * printStats()
 *
 * Prints calculated stats
 */
void Hash::printStats()
{
    cout << "Total Collisions = " << collisions << endl;
    cout << "Longest List Ever = " << longestList << endl;
    cout << "Average List Length Over Time = " << runningAvgListLength << endl;
    cout << "Load Factor = " << loadFactor << endl;
    
}


/**
 * processFile()
 *
 * Opens text file passed in, and processes it into a hash table
 *
 * @params filename    The name of the input file.
 */
void Hash::processFile(string fileName)
{
    std::ifstream stream;
    string str = "";

    stream.open(fileName);

    // for each line of the input text file
    while(std::getline(stream, str))
    {
        int hashIndex = hf(str);    // hash function that returns a key

        if (!hashTable[hashIndex].empty())  // if key slot is not empty
        {
            ++collisions;
            unsigned int listSize = (hashTable[hashIndex].size() + 1);
            // checks to see if this is the longest list
            if (listSize > longestList)
            {
                longestList = listSize;
            }
        }
        hashTable[hashIndex].push_back(str);
        runningAvgListLength = (runningAvgListLength + avgLength()) / 2.0;
    }
    stream.close();
}


/**
 * remove()
 *
 * Removes passed in word from hash table
 *
 * @params word    The name of the word to remove from hash table
 */
void Hash::remove(string word)
{
    if (search(word))           // if it finds the word
    {
        int hashIndex = hf(word);   // hash function that returns a key
        hashTable[hashIndex].remove(word);  // removes word
        runningAvgListLength = (runningAvgListLength + avgLength()) / 2.0;
    }
}


/**
 * search()
 *
 * Searches hash table for word passed in
 *
 * @params word    The name of the word to find in hash table
 */
bool Hash::search(string word)
{
    int hashIndex = hf(word);   // hash function that returns a key

    list<string>::iterator iter;
    if (!hashTable[hashIndex].empty())  // if slot is not empty
    {
        for (iter = hashTable[hashIndex].begin(); 
            iter != hashTable[hashIndex].end(); ++iter)
        {
            // if word is in list, return true
            if (*iter == word)
            {
                return true;
            }
        }
    }
    return false;
}
