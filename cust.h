// cust.h
// Jones, Troy
// tjones71
#include <string>
#include <iostream>
#include <fstream>

class Cust
{
public:
    Cust();
    Cust(std::string name, bool shopper, int arrivalTime, int numOfItems)
        {
            mName = name;
            mShopper = shopper;
            mArrivalTime = arrivalTime;
            mNumOfItems = numOfItems;
            mCheckoutTime = mArrivalTime + (numOfItems * 2);
            mNetOwed = numOfItems * 3;
            mTimeRobberLeft = 0;
        } 

    // returns the time the cust arrives at the mart
    int getArrivalTime(Cust*);
        
    // returns the time the cust is ready to checkout
    int getCheckoutTime(Cust*);

    // returns the cust name
    std::string getCustName(Cust*);

    // returns the amount the cust owes
    int getNetOwed(Cust*);

    // returns the num of items cust has
    int getNumItems(Cust*);

    // returns whether the cust is shopper or robber
    bool isShopper(Cust*);

    // returns the time the robber left the mart
    int getTimeRobberLeft(Cust*);

    // return the time the cust is done getting items
    int getTimeShoppingDone(Cust*);

    // print functions
    void printCheckingOut(std::ofstream&, int, std::string, int);
    void printDoneShopping(std::ofstream&, int, std::string);
    void print_entered(std::ofstream&, int, std::string);
    void printPaid(std::ofstream&, int, std::string, int, int, int);
    void printRobbed(std::ofstream&, int, std::string, int, int, int);
    void printStartChecking(std::ofstream&, int, std::string, int);
    void setTimeRobberLeft(int);

private:
    std::string mName;
    bool mShopper;
    int mArrivalTime;
    int mNumOfItems;
    int mCheckoutTime;
    int mNetOwed;
    int mTimeRobberLeft;
};