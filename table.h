/**
* @file table.h
*
* @brief
*    Declaration of a class to represent a restaurant table.
*
* 
* @date 1/1/16
*/

#ifndef CSCI_311_TABLE_H
#define CSCI_311_TABLE_H

#include <string>
#include "party.h"

using std::string;

class Table {

public:
    Table();
    Table(const string& tableID, int numSeats, const string& serverName);
    ~Table();
    const string* getTableID() const { return tableID; }
    int getNumSeats() const { return numSeats; }
    const string* getServerName() const { return serverName; }
    void decrementTimer() { timer--; }
    int getTimer() const { return timer; }
    void setTimer(int duration) { timer = duration; }
    const Party* getParty() { return party; }
    void seatParty(const Party* newParty);
    void clearTable() { party = nullptr; timer = 0; }

private:
    string* tableID;        
    int numSeats;           
    string* serverName;     
    int timer;              
    const Party* party;     
};

#endif // CSCI_311_TABLE_H
