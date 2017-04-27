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

///////////////////////////////////////////////

void RBapp::mainLoop()
{
    string command = "";

    while (cin >> command)
    {
        app.processCommand(command);
    }
}

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