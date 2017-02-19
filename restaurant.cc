/**
* @file restaurant.cc
*
* @brief contains main(), retrieves the input from the input file, implements
*    the rest of the program.
*
* @author Troy Jones
* @date 2/19/17
*/
#include <iostream>
#include "restaurant.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/**
* @brief   Main(). Executes program
* @param   none
* @return  0
*
*/
int main()
{

    Restaurant joesDiner;
    joesDiner.getInput(); 
    joesDiner.serveParties();

    return 0;

}

/**
* @brief   takes input text and places words in doubly linked lists
* @param   none
* @return  none
*
*/
void Restaurant::getInput()
{
    string feed = "";
    string ID = "";
    string server = "";
    string reservationName = "";
    int seats = 0;
    int numDiners = 0;
    int timeRequired = 0;

    while(cin >> feed)
    {
        if(feed == "table")
        {
            cin >> ID;
            cin >> seats;
            cin >> server;
            available.append(new Table(ID, seats, server));
        }
        else if(feed == "party")
        {
            cin >> numDiners;
            cin >> reservationName;
            cin >> timeRequired;
            waiting.append(new Party(reservationName,numDiners,timeRequired));
        }
    }
}

/**
* @brief   takes party off waiting, appends them to available table and places
*           them on occupied list. Decrements timer, evicts party and puts 
*           the table back on the available list, for as long as there is a 
*           waiting party.
* @param   none
* @return  none
*
*/
void Restaurant::serveParties()
{
    do
    {
        /***********************************
        ** takes people off occupied list **
        ***********************************/
        Table* curOccupied = occupied.first();
        while (curOccupied != NULL)
        {
            curOccupied->decrementTimer();

            if(curOccupied->getTimer() == 0)
            {
                cout << *curOccupied->getParty()->getReservationName() << 
                    " finished at " << *curOccupied->getTableID() << endl;

                available.append(curOccupied);
                curOccupied->clearTable();
                curOccupied = occupied.remove();
            }
            else
                curOccupied = occupied.next();
        }

        /*********************************************
        ** seats waiting partys at available tables **
        *********************************************/
        if (!waiting.empty() && !available.empty())
            for(Party* curParty = waiting.first(); curParty; 
                curParty = waiting.next())
            {
                Table* curTable = available.first();
                if (curTable == NULL || curParty == NULL)
                        break;
                while(curTable)
                {
                    if (curTable == NULL || curParty == NULL)
                        break;

                    if(curTable->getNumSeats() >= curParty->getNumDiners())
                    {
                        cout << *curParty->getReservationName() << 
                            " seated at " << *curTable->getTableID() << endl;

                        servers[*curTable->getServerName()] += 
                            curParty->getNumDiners();

                        curTable->seatParty(curParty);
                        occupied.append(curTable);
                        available.remove();
                        curTable = available.first();
                        curParty = waiting.remove();
                    }
                    else
                        curTable = available.next();
                }
            }
    }
    while(!waiting.empty() || !occupied.empty());

    for (std::map<string,int>::iterator it = servers.begin(); 
        it != servers.end(); ++it)
        cout << it->first << " served " << it->second << endl;

}
