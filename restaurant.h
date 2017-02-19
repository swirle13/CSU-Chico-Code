/**
* @file restaurant.h   Declaration of a restaurant.
*
* @brief
*    Simulates seating diners in a restaurant.
*
* 
* @date 1/1/16
*/

#ifndef CSCI_311_RESTAURANT_H
#define CSCI_311_RESTAURANT_H

#include <string>
#include <map>
#include "doublylinkedlist.h"
#include "table.h"
#include "party.h"

// Note! Put main() in restaurant.cpp
// It should instantiate a Restaurant object and call functions on it.
// Restaurant myDiner; myDiner.getInput(); myDiner.serveParties();

class Restaurant {
public:
    void getInput();               
    void serveParties();   

private:
    DoublyLinkedList<Table> available;  
    DoublyLinkedList<Table> occupied;   
    DoublyLinkedList<Party> waiting;    
    std::map<std::string,int> servers;  
};

#endif // CSCI_311_RESTAURANT_H
