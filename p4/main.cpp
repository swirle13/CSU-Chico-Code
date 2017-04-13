#include "minpriority.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// counts number of spaces in line passed in
int countSpacesInStr(string);




int main()
{
    char desiredAction;
    string str = "";
    unsigned int key = 0;
    MinPriorityQ q;

    while (cin >> desiredAction)    
    {
        switch(desiredAction)
        {
        case 'a':
            cin >> str;
            cin >> key;
            q.insert(str, key);
            break;
        case 'd':
            cin >> str;
            cin >> key;
            q.decreaseKey(str, key);
            break;
        case 'x':
            // get and print lowest value
            cout << q.extractMin() << endl;            
            break;
        case 'q':
            exit(0);
            break;
            // default:
            //     break;
        }
    }
    return 0;
}


/**
 *  @brief:     counts the number of spaces in a string and returns the value
 *  @params:    string str
*/
int countSpacesInStr(string str)
{
    int count = 0;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        if (str[i] == 32)   // 32 == " "
        {
            ++count;
        }
    }
    return count;
}
