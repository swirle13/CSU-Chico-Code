// sim.cpp
// Jones, Troy
// tjones71
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "pqueue.h"
using namespace std;

struct Checker
{
    int cashRegister = 100;
    int timeAvail = 0;
    bool available = true;
    Cust* cust = NULL;
};

// puts custs in arrival queue
void insertCustomers(Pqueue&, streambuf*);

// well... it runs the simulation
void runSimulation(Pqueue&, int, int, ofstream&);

// Verifies that arguments that are passed in at the command prompt are good.
void verifyStartup(int, char*[], int&, int&, bool&);

/////////////////////////////////////////////////////////////////////
//  Main()  /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int numOfCheckers = -1;
    int checkerBreakLength = -1;
    bool shopper = false;

    verifyStartup(argc, argv, numOfCheckers, checkerBreakLength, shopper);

    // initialize input file stream
    ifstream my_ifile(argv[3]);
    if (!my_ifile)
    {
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        return 1;
    }

    // initialize output file stream
    ofstream my_ofile(argv[4]);
    if (!my_ofile)
    {
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        return 1;
    }

    streambuf* buffer = my_ifile.rdbuf();
    Pqueue arrivalQ;

    // inserts custs into arrivalQ
    insertCustomers(arrivalQ, buffer);

    runSimulation(arrivalQ, numOfCheckers, checkerBreakLength, my_ofile);

    return 0;
}
/////////////////////////////////////////////////////////////////////
//  Definitions  ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void insertCustomers(Pqueue& arrivalQ, streambuf* buffer)
{
    string str = "";

    int sortingArgument = 0;
    string name = "";
    bool shopper = false;
    int arrivalTime = 0;
    int numOfItems = 0;

    while (buffer->sgetc() != -1)
    {
        if (buffer->sgetc() == ' ')
        {
            switch (sortingArgument)
            {
                case 0: // name
                    name = str;
                    str = "";
                    sortingArgument++;
                    buffer->sbumpc();
                break;
                case 1: // shopper/robber
                    if (str == "shopper")
                        shopper = true;
                    else
                        shopper = false;
                    str = "";
                    sortingArgument++;
                    buffer->sbumpc();
                break;
                case 2:
                    arrivalTime = stoi(str);
                    str = "";
                    sortingArgument++;
                    buffer->sbumpc();
                break;
            }
        }
        else if (buffer->sgetc() == 10) // \n
        {
            if (sortingArgument == 3)
            {
                numOfItems = stoi(str);
                arrivalQ.createCust(name, shopper, arrivalTime, numOfItems);
                arrivalQ.tallyCustomer();
                sortingArgument = 0;
                str = "";
                buffer->sbumpc();    
            }
            else
                cout << "fail" << endl;
        }
        else
        {
            str += buffer->sbumpc();
        }
    }
}

void runSimulation(Pqueue& arrivalQ, int numOfCheckers, int checkerBreakLength, ofstream& my_ofile)
{
    Pqueue shoppingQ;
    Pqueue waitingForCheckerQ;
    Cust cust;
    Checker* checkerArray = new Checker[numOfCheckers];
    int checkerNumber = 0;
    int custsAtCheckers = arrivalQ.getNumCustomers();
	bool started = false;
    int clock;

    // well... you didn't say we couldn't  :)
    if (checkerBreakLength > 100)
        checkerBreakLength = 0;

    /////////////////////////
    // Loop for Simulation //
    /////////////////////////

    for (clock = 1; custsAtCheckers > 0; clock++)
    {

		// pops custs off arrivalQ and puts them on shoppingQ
        while (arrivalQ.getNumCustomers() != 0 && arrivalQ.getTimeEnteredStore(arrivalQ) == clock)
        {
            // get and print customer name
            string name = cust.getCustName(arrivalQ.getCustomer(arrivalQ));
            cust.print_entered(my_ofile, clock, name);

            // take customer off arrivalQ and puts them on shoppingQ
            shoppingQ.transferToQ(arrivalQ, shoppingQ);
        }



        // if custs shopping
        if (shoppingQ.getNumCustomers() > 0 || custsAtCheckers > 0)
        {


            // if cust done shopping 
            while (shoppingQ.getNumCustomers() > 0 && shoppingQ.getTimeDoneShopping(shoppingQ) == clock)
            {
                // prints done shopping message and puts on another Q to wait for checker
                cust.printDoneShopping(my_ofile, clock, cust.getCustName(shoppingQ.getCustomer(shoppingQ)));
                waitingForCheckerQ.transferToQ(shoppingQ, waitingForCheckerQ);
            }


				// looks for available checker
				for (checkerNumber = 0; checkerNumber <= (numOfCheckers - 1); checkerNumber++)
				{

                    // if checker has robber
                    if (checkerArray[checkerNumber].cust && checkerArray[checkerNumber].cust->isShopper(checkerArray[checkerNumber].cust) == false && checkerArray[checkerNumber].cust->getTimeRobberLeft(checkerArray[checkerNumber].cust) == clock)
                    {
                        int numItems = checkerArray[checkerNumber].cust->getNumItems(checkerArray[checkerNumber].cust);

                        checkerArray[checkerNumber].cust->printRobbed(my_ofile, checkerArray[checkerNumber].cust->getTimeRobberLeft(checkerArray[checkerNumber].cust), checkerArray[checkerNumber].cust->getCustName(checkerArray[checkerNumber].cust), checkerArray[checkerNumber].cashRegister, numItems, checkerNumber);
                    }


                    // if checker has cust but will be available
                    if (checkerArray[checkerNumber].cust && checkerArray[checkerNumber].timeAvail <= clock)
                    {
                        int numItems = checkerArray[checkerNumber].cust->getNumItems(checkerArray[checkerNumber].cust);


                        // if shopper
                        if (checkerArray[checkerNumber].cust->isShopper(checkerArray[checkerNumber].cust))
                        {
                            checkerArray[checkerNumber].cust->printPaid(my_ofile, clock, checkerArray[checkerNumber].cust->getCustName(checkerArray[checkerNumber].cust), (numItems * 3), numItems, checkerNumber);
                            custsAtCheckers--;
                            checkerArray[checkerNumber].available = true;
                            checkerArray[checkerNumber].cust = NULL;
                        }
                        // if robber
                        else
                        {
                            checkerArray[checkerNumber].cashRegister = 0;
                            custsAtCheckers--;
                            checkerArray[checkerNumber].available = true;
                            checkerArray[checkerNumber].cust = NULL;
                        }
                    }
                }


                // looks for available checker
                for (checkerNumber = 0; checkerNumber <= (numOfCheckers - 1); checkerNumber++)
                {    

					// if checker available and cust is done shopping
					if (checkerArray[checkerNumber].available && waitingForCheckerQ.getNumCustomers() > 0 && waitingForCheckerQ.getTimeDoneShopping(waitingForCheckerQ) <= clock)
					{
						// get and print customer name
						string name = cust.getCustName(waitingForCheckerQ.getCustomer(waitingForCheckerQ));
						cust.printStartChecking(my_ofile, clock, name, checkerNumber);

						// sets checker to unavailable
						checkerArray[checkerNumber].available = false;

						// puts shopper with checker
						checkerArray[checkerNumber].cust = waitingForCheckerQ.dequeueCustomer(waitingForCheckerQ);



						// shopper: calculates when the checker will be available next
						if (checkerArray[checkerNumber].cust->isShopper(checkerArray[checkerNumber].cust))
						{
							int numItems = checkerArray[checkerNumber].cust->getNumItems(checkerArray[checkerNumber].cust);

							checkerArray[checkerNumber].timeAvail = clock + numItems;
							checkerArray[checkerNumber].cashRegister += (numItems * 3);
						}
						// robber: calculates when the checker will be available next 
						else
						{
							int numItems = checkerArray[checkerNumber].cust->getNumItems(checkerArray[checkerNumber].cust);

							checkerArray[checkerNumber].timeAvail = clock + 5 + checkerBreakLength;
                            checkerArray[checkerNumber].cust->setTimeRobberLeft(clock + 5);
						}
					}
                }
        }


        // if all custs have checked out
        if (custsAtCheckers == 0)
        {
            clock++;
            break;
        }
    }



    for (checkerNumber = 0; checkerNumber < (numOfCheckers); checkerNumber++)
    {
        my_ofile << "registers[" << checkerNumber << "] = $" << checkerArray[checkerNumber].cashRegister << endl;
    }

    my_ofile << "time = " << clock << endl;
}

void verifyStartup(int argc, char* argv[], int& numOfCheckers, int& checkerBreakLength, bool& shopper)
{
    for (int i = 0; i < argc; i++)
    {
        //////////////////////////////////////////////////////
        // checks to verify the proper number of arguments  //
        //////////////////////////////////////////////////////
        if (argc != 5)
        {
            cerr << "Error: invalid number of command line arguments." << endl;
            exit(1);
        }
        ////////////////////////////////////
        // checks for amount of checkers  //
        ////////////////////////////////////
        else if (i == 1)
        {
            string strNumOfCheckers = "";
            int j = 0;

            while (argv[i][j] != NULL)
            {
                if (isdigit(argv[i][j]))
                {
                    strNumOfCheckers += argv[i][j];
                    j++;            
                }
                else
                {
                    cerr << "Error: invalid number of checkers specified." << endl;
                    exit(1);
                }
            }
            // parse from str to int
            numOfCheckers = stoi(strNumOfCheckers);
            // verify number of checkers
            if (numOfCheckers > 0)
            {
                continue;
            }
            else
            {
                cerr << "Error: invalid number of checkers specified." << endl;
                exit(1); 
            }
        }
        ///////////////////////////////////////
        // checks for checkers break length  //
        ///////////////////////////////////////
        else if (i == 2)
        {
            string strBreakLength = "";
            int j = 0;

            while (argv[i][j] != NULL)
            {
                if (isdigit(argv[i][j]))
                {
                    strBreakLength += argv[i][j];
                    j++;            
                }
                else
                {
                    cerr << "Error: invalid checker break duration specified." << endl;
                    exit(1);
                }
            }
            // parse from str to int
            checkerBreakLength = stoi(strBreakLength);
            // verify number of checkers
            if (checkerBreakLength >= 0)
            {
                continue;
            }
            else
            {
                cerr << "Error: invalid checker break duration specified." << endl;
                exit(1); 
            }
        }
    }
}

