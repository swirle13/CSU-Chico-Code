/* This assignment originated at UC Riverside.*/

/**
 * @file hash_function.cpp   Provides a function to the caller.
 * 
 * @brief
 *  Takes a string as input and parses it to its ASCII value. It
 * then takes that value and manipulates it to a unique value to be
 * passed as a key.
 *
 * @author Judy Challinger and Troy Jones
 * @date 3/30/17
 */

#include <string>
#include "hash.h"

using std::string;

// This is only a sample hash function (and a bad one at that). You will
// need to replace the contents of this hash function with your own
// hash function

int Hash::hf(string ins)
{
  // place your hash function here....
    unsigned int result = 0;

    result += static_cast<int>(ins[0]);
    result *= static_cast<int>(ins[1]);
    result += static_cast<int>(ins[2]);
    result *= static_cast<int>(ins[3]);
    result += static_cast<int>(ins[4]);

    return (result % HASH_TABLE_SIZE);

    //   return ((int)ins[0] % HASH_TABLE_SIZE);    // original hash function
}
