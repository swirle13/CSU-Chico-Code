/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger and Troy Jones
 * @date 2/22/17
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include "CensusData.h"

/**
 * insertionSort
 *
 * Helper function that determines whether to sort by city name or population.
 *
 * @param type The type of sort desired by the calling function.
 */
void CensusData::insertionSort(int type) 
{

    if (type == 0)      // sort by population ascending
    {
       insertionSortByPop(data);
    }
    else if (type == 1) // sort by name ascending
    {
        insertionSortByName(data);
    }
    else
    {
        std::cerr << "Not valid sort type" << std::endl;
    }

}


/**
 * mergeSort
 *
 * Helper function that determines whether to sort by city name or population.
 *
 * @param type The type of sort desired by the calling function.
 */
void CensusData::mergeSort(int type) 
{

    if (type == 0)      // sort by population ascending
    {
        mergeSortByPop(data, 0, (getSize() - 1));
    }
    else if (type == 1) // sort by name ascending
    {
        mergeSortByName(data, 0, (getSize() - 1));
    }
    else
    {
        std::cerr << "Not valid sort type" << std::endl;
    }

}


/**
 * quickSort
 *
 * Helper function that determines whether to sort by city name or population.
 *
 * @param type The type of sort desired by the calling function.
 */
void CensusData::quickSort(int type) 
{

    if (type == 0)      // sort by population ascending
    {
        quickSortByPop(data, 0, (getSize() - 1));
    }
    else if (type == 1) // sort by name ascending
    {
        quickSortByName(data, 0, (getSize() - 1));
    }
    else
    {
        std::cerr << "Not valid sort type" << std::endl;
    }

}


/**
 * insertionSortByPop
 *
 * Does insertion sort by population.
 *
 * @param data  Vector containing the data inserted from main()
 */
void CensusData::insertionSortByPop(std::vector<Record*>& data)
{

    Record* key;

    // goes through data linearly
    for (int j = 1; j < getSize(); j++)
    {
        key = data[j];

        // compares currently indexed population with one stored in key
        int i = j - 1;
        while (i >= 0 && data[i]->population > key->population)
        {
            data[i + 1] = data[i];
            i -= 1;
        }

        data[i + 1] = key;
    }

}


/**
 * insertionSortByName
 *
 * Does insertion sort by name.
 *
 * @param data  Vector containing the data inserted from main()
 */
void CensusData::insertionSortByName(std::vector<Record*>& data)
{

    Record* key;

    // goes through data linearly
    for (int j = 1; j < getSize(); j++)
    {
        key = data[j];

        // compares currently indexed city with one stored in key
        int i = j - 1;
        while (i >= 0 && *data[i]->city > *key->city)
        {
            data[i + 1] = data[i];
            i -= 1;
        }

        data[i + 1] = key;
    }  

}


/**
 * mergeSortByPop
 *
 * Implements recursion part of merge sort for population
 *
 * @param arr  Data passed in from calling function
 * @param start  The starting index of the array being passed in
 * @param end  The last index of the array being passed in
 */
void CensusData::mergeSortByPop(std::vector<Record*>& arr, int start, int end)
{

    if (start < end)
    {
        int mid = ((start + end) / 2);
        mergeSortByPop(arr, start, mid);
        mergeSortByPop(arr, (mid + 1), end);
        mergePop(arr, start, mid, end);
    }

}


/**
 * mergePop
 *
 * Separates the array being passed in, into a left and right array. Then it 
 * sorts in ascending order, depending on population.
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param mid  Midpoint of vector being passed in.
 * @param end  End index of vector being passed in.
 */
void CensusData::mergePop(std::vector<Record*>& arr,
 int start, int mid, int end)
{

    std::vector<Record*> L; // left vector
    std::vector<Record*> R; // right vector

    // inserts items into vector from starting index to midpoint
    for (int i = start; i < (mid + 1); i++)
        L.push_back(arr[i]);

    // inserts items into right vector from 1 after midpoint to end of arr
    for (int j = (mid + 1); j <= end; j++)
        R.push_back(arr[j]);

    // inserting NULL for an end of array flag
    L.push_back(NULL);
    R.push_back(NULL);

    // iterators for 'for' loop
    int i = 0;
    int j = 0;

    /* sorts left and right array, and inserts them back into original 
        array sorted */
    for (int k = start; k <= end; k++)
    {
        // if either comparator is at sentinel
        if (L[i] == NULL || R[j] == NULL)
        {
            if (R[j] == NULL)
            {
                arr[k] = L[i];
                i++;
            }
            else 
            {
                arr[k] = R[j];
                j++;
            }
        }
        // if left array pop is less than right array pop
        else if (L[i]->population <= R[j]->population)
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
    }

    // empties both vectors
    L.clear();
    R.clear();

}


/**
 * mergeSortByName
 *
 * Does the recursive work of dividing data to singular arrays.
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
void CensusData::mergeSortByName(std::vector<Record*>& arr, int start, int end)
{

    if (start < end)
    {
        int mid = ((start + end) / 2);
        mergeSortByName(arr, start, mid);
        mergeSortByName(arr, (mid + 1), end);
        mergeName(arr, start, mid, end);
    }

}


/**
 * mergeName
 *
 * Separates the array being passed in, into a left and right array. Then it 
 * sorts in ascending order, depending on city name.
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
void CensusData::mergeName(std::vector<Record*>& arr,
 int start, int mid, int end)
{

    std::vector<Record*> L; // left vector
    std::vector<Record*> R; // right vector

    // inserts items into vector from starting index to midpoint
    for (int i = start; i < (mid + 1); i++)
    {
        L.push_back(arr[i]);
    }

    // inserts items into right vector from 1 after midpoint to end of arr
    for (int j = (mid + 1); j <= end; j++)
    {
        R.push_back(arr[j]);
    }

    // inserting NULL for an end of array flag
    L.push_back(NULL);
    R.push_back(NULL);

    // iterators for 'for' loop
    int i = 0;
    int j = 0;

    /* sorts left and right array, and inserts them back into original 
        array sorted */
    for (int k = start; k <= end; k++)
    {
        // if either comparator is at sentinel
        if (L[i] == NULL || R[j] == NULL)
        {
            if (R[j] == NULL)
            {
                arr[k] = L[i];
                i++;
            }
            else 
            {
                arr[k] = R[j];
                j++;
            }
        }
        // if left array city name alpha is less than right array city alpha
        else if (*L[i]->city <= *R[j]->city)
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
    }

    // empties both vectors
    L.clear();
    R.clear();

}


/**
 * quickSortByPop
 *
 * Does the recursive work of comparing and sorting.
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
void CensusData::quickSortByPop(std::vector<Record*>& arr, int start, int end)
{

    if (start < end)
    {
        int pivot = popPartion(arr, start, end);
        quickSortByPop(arr, start, (pivot - 1));
        quickSortByPop(arr, (pivot + 1), end);
    }

}


/**
 * popPartion
 *
 * Picks a random index as a pivot and sorts accordingly
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
int CensusData::popPartion(std::vector<Record*>& arr, int start, int end)
{

    // instantiates a random number genertator
    unsigned int seed = 
        std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(start, end);
    int rand = distribution(generator);

    // puts random record at end for pivot
    Record* temp = arr[rand];
    arr[rand] = arr[end];
    arr[end] = temp;
    int pivot = arr[end]->population;
    int i = start - 1;

    // iterates through data
    for (int j = start; j < end; j++)
    {
        if (arr[j]->population <= pivot)
        {
            i += 1;
            // swapping records
            Record* temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }

    // swapping records
    temp = arr[end];
    arr[end] = arr[i + 1];
    arr[i + 1] = temp;

    return (i + 1);

}


/**
 * quickSortByName
 *
 * Does the recursive work of comparing and sorting.
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
void CensusData::quickSortByName(std::vector<Record*>& arr, int start, int end)
{

    if (start < end)
    {
        int pivot = namePartion(arr, start, end);
        quickSortByName(arr, start, (pivot - 1));
        quickSortByName(arr, (pivot + 1), end);
    }

}


/**
 * namePartion
 *
 * Picks a random index as a pivot and sorts accordingly
 *
 * @param arr  Vector data being passed in by calling function.
 * @param start  Starting index of vector being passed in.
 * @param end  End index of vector being passed in.
 */
int CensusData::namePartion(std::vector<Record*>& arr, int start, int end)
{

    // instantiates a random number genertator
    unsigned int seed = 
    std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(start, end);
    int rand = distribution(generator);

    // puts random record at end for pivot
    Record* temp = arr[rand];
    arr[rand] = arr[end];
    arr[end] = temp;
    string pivot = *arr[end]->city;
    int i = start - 1;

    // iterates through data
    for (int j = start; j < end; j++)
    {
        if (*arr[j]->city <= pivot)
        {
            i += 1;
            // swapping records
            Record* temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }

    // swapping records
    temp = arr[end];
    arr[end] = arr[i + 1];
    arr[i + 1] = temp;

    return (i + 1);

}