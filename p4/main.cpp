/**
 * @file main.cpp
 *
 * @brief
 *  Executes a program to test user input to utilize a minimum priority heap.
 *
 * @author Troy Jones (tjones71)
 * @date 4/13/17
 */

#include "minpriority.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

int main()
{
    char desiredAction;     // what function the user wants
    string str = "";
    unsigned int key = 0;   // priority
    MinPriorityQ q;         // the queue

    while (cin >> desiredAction)    
    {
        switch(desiredAction)
        {
        case 'a':           // user wishes to add name & key
            cin >> str;
            cin >> key;
            q.insert(str, key);
            break;
        case 'd':           // user wishes to change key of name inserted
            cin >> str;
            cin >> key;
            q.decreaseKey(str, key);
            break;
        case 'x':           // get and print first name in q
            cout << q.extractMin() << endl; 
            break;
        case 'q':           // exit program
            exit(0);
            break;
        }
    }
    return 0;
}
