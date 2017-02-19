/**
* @file party.cc
*
* @brief includes constructor for Party
*    
*
* @author Troy Jones
* @date 2/19/17
*/
#include "party.h"

/**
* @brief   party class constructor
* @param   string, int, int
* @return  party class
*
*/
Party::Party(const string& name, int diners, int time)
{
    this->reservationName = new std::string(name);
    this->numDiners = diners;
    this->timeRequired = time;
}

/**
* @brief   empty constructor 
*
*/
Party::Party(){}

/**
* @brief   empty destructor
*
*/
Party::~Party(){}