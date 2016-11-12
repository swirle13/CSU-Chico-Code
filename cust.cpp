// cust.cpp
// Jones, Troy
// tjones71
#include "cust.h"
#ifndef CUST_H
#define CUST_H
using namespace std;

Cust::Cust()
{

}

int Cust::getArrivalTime(Cust* cust)
{
    return cust->mArrivalTime;
}

int Cust::getCheckoutTime(Cust* cust)
{
    return cust->mCheckoutTime;
}

string Cust::getCustName(Cust* cust)
{
    return cust->mName;
}

int Cust::getNetOwed(Cust* cust)
{
    return cust->mNetOwed;
}

int Cust::getNumItems(Cust* cust)
{
    return cust->mNumOfItems;
}

bool Cust::isShopper(Cust* cust)
{
    return cust->mShopper;
}

int Cust::getTimeRobberLeft(Cust* cust)
{
    return cust->mTimeRobberLeft;
}

int Cust::getTimeShoppingDone(Cust* cust)
{
    return cust->mCheckoutTime;
}

void Cust::printCheckingOut(ofstream& my_ofile, int clock, string name, int checkerNum)
{
    my_ofile << clock << ": " << name << " started checkout with checker " << checkerNum << endl; 
}

void Cust::printDoneShopping(ofstream& my_ofile, int clock, string name)
{
    my_ofile << clock << ": " << name << " done shopping" << endl;
}

void Cust::print_entered(ofstream& my_ofile, int clock, string name)
{
    my_ofile << clock << ": " << name << " entered store" << endl;
}

void Cust::printPaid(ofstream& my_ofile, int clock, string name, int paid, int numItems, int checkerNum)
{
    if (numItems > 1)
        my_ofile << clock << ": " << name << " paid $" << paid << " for " << numItems << " items to checker " << checkerNum << endl;
    else
        my_ofile << clock << ": " << name << " paid $" << paid << " for " << numItems << " item to checker " << checkerNum << endl;
}

void Cust::printRobbed(ofstream& my_ofile, int clock, string name, int stole, int numItems, int checkerNum)
{
    if (numItems > 1)
        my_ofile << clock << ": " << name << " stole $" << stole << " and " << numItems << " items from checker " << checkerNum << endl;
    else
        my_ofile << clock << ": " << name << " stole $" << stole << " and " << numItems << " item from checker " << checkerNum << endl;
}

void Cust::printStartChecking(ofstream& my_ofile, int clock, string name, int checkerNum)
{
    my_ofile << clock << ": " << name << " started checkout with checker " << checkerNum << endl;
}

void Cust::setTimeRobberLeft(int timeRobberLeft)
{
    mTimeRobberLeft = timeRobberLeft;
}

#endif