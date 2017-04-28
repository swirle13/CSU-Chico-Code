/**
 * @file    rbapp.cpp
 * 
 * @brief   Functions that pertain to rbapp.h
 * 
 * @author  Troy Jones
 * @date    4/27/17
 */ 
#include "rbapp.h"
#include <cctype>

using std::cout;
using std::cin;
using std::endl;

RBTree rbTree;
RBapp app;

int main()
{
    app.mainLoop();
}

/**
 * mainLoop()
 *
 * Initiates the main program
 */
void RBapp::mainLoop()
{
    string command = "";

    while (cin >> command)
    {
        app.processCommand(command);
    }
}

/**
 * processCommand()
 *
 * Processes the command input, and delegates from there
 *
 * @param command The command passed in
 *
 * @return bool Returns true or false to the calling function to determine
 *              whether to continue with the program or not
 */
bool RBapp::processCommand(string& command)
{
    if(command == "insert")
    {
        string keyAndData = "";
        cin.ignore();
        getline(cin, keyAndData);
        app.processInsert(keyAndData);
        return true;
    }
    else if(command == "print")
    {
        app.processPrint();
        return true;
    }
    else if(command == "find")
    {
        string key = "";
        cin.ignore();
        cin >> key;
        app.processFind(key);
        return true;
    }
    else if(command == "delete")
    {
        string keyAndData = "";
        cin.ignore();
        getline(cin, keyAndData);
        app.processDelete(keyAndData);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * processDelete()
 *
 * Splits the inputted key and data and passes them into a private delete
 *  function
 *
 * @param keyAndData The key and satellite data
 */
void RBapp::processDelete(string& keyAndData)
{
    string key = "";
    string data = "";

    int pos = keyAndData.find(" ");
    key = keyAndData.substr(0, pos);
    data = keyAndData.substr(pos + 1, keyAndData.length());

    rbTree.rbDelete(key, data);
}

void RBapp::processFind(string& key)
{
    vector<const string*> keysFound;
    vector<const string*>::iterator it;

    keysFound = rbTree.rbFind(key);

    for (it = keysFound.begin(); it < keysFound.end(); ++it)
    {
        cout << key << " " << *(*it) << endl;
    }
}

void RBapp::processInsert(string& keyAndData)
{
    string key = "";
    string data = "";

    int pos = keyAndData.find(" ");
    key = keyAndData.substr(0, pos);
    data = keyAndData.substr(pos + 1, keyAndData.length());

    rbTree.rbInsert(key, data);
}

void RBapp::processPrint()
{
    rbTree.rbPrintTree();
}