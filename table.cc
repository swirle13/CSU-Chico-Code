/**
* @file table.cc
*
* @brief includes constructor for Table, also seats party at table.
*    
*
* @author Troy Jones
* @date 2/19/17
*/

#include "table.h"

/**
* @brief   table party constructor
* @param   string, int, string
* @return  table class
*
*/
Table::Table(const string& tableID, int numSeats, const string& serverName)
{
    this->tableID = new std::string(tableID);
    this->numSeats = numSeats;
    this->serverName = new std::string(serverName);
}

/**
* @brief   empty constructor
*
*/
Table::Table(){}

/**
* @brief   empty destructor
*
*/
Table::~Table(){}

/**
* @brief   assigns pointer to party var, sets dining timer
* @param   party class pointer
* @return  none
*
*/
void Table::seatParty(const Party* newParty)
{
    party = newParty;
    timer = newParty->getTimeRequired();
}

