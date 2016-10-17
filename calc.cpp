// calc.cpp
// Jones, Troy
// tjones71
#include "dstack.h"
using std::cin;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void doMath(Dstack&, char, int&);   /* holds functions to complete 
                                       '+', '-', '*', '/', '^' */
void error();   // prints error message and returns 1
bool isOperator(char);  // checks to see if char is an operator

/////////////////////////////////////////////////////////////////////
int main()
{

    char charCommand;
    bool oper = false;
    double operand = 0.0;
    int itemsInStack = 0;
    int decInNum = 0;

    Dstack dstack;

    while(cin.peek() != -1)
    {
		if (cin.peek() != '.' && isspace(cin.peek()))
    	{
        	cin.ignore();
            decInNum = 0;
        }    
        else if (isOperator(cin.peek()))
        {
            if (itemsInStack > 1)
            {
                cin >> charCommand;
                doMath(dstack, charCommand, itemsInStack);
            }
            else
                error();
        }
        else if (isdigit(cin.peek()) || cin.peek() == '.')
        {                
            if (decInNum == 0)
            {
                cin >> operand;
                dstack.push(operand, itemsInStack);       
                decInNum++;         
            }
            else
                error();
        }
        else
            error();
    }    

    if (itemsInStack == 1)
        cout << dstack.pop(itemsInStack) << endl;
    else
        error();       

    return 0;
}
/////////////////////////////////////////////////////////////////////

void doMath(Dstack& dstack, char charCommand, int& itemsInStack)
{
    double operand1 = 0.0;
    double operand2 = 0.0;
    double result = 0.0;

    switch (charCommand)
    {
        case '^':
            if (!dstack.empty(itemsInStack))
            {
                operand1 = dstack.pop(itemsInStack);
                operand2 = dstack.pop(itemsInStack);
                if (operand1 < 0)
                {
                    error();
                }
                result = pow(operand2, operand1);
                dstack.push(result, itemsInStack);    
            }
            else
                error();
        break;
        case '/':
            if (!dstack.empty(itemsInStack))
            {
                operand1 = dstack.pop(itemsInStack);
                operand2 = dstack.pop(itemsInStack);
            }
            if (operand2 != 0.0)
            {
                result = operand2 / operand1;
                dstack.push(result, itemsInStack);
            }
            else
            {
                error();
            }
        break;
        case '*':
            if (!dstack.empty(itemsInStack))
            {
                operand1 = dstack.pop(itemsInStack);
                operand2 = dstack.pop(itemsInStack);
                result = operand1 * operand2;
                dstack.push(result, itemsInStack);                
            }
            else
                error();
        break;
        case '-':
            if (!dstack.empty(itemsInStack))
            {
                operand1 = dstack.pop(itemsInStack);
                operand2 = dstack.pop(itemsInStack);
                result = operand2 - operand1;
                dstack.push(result, itemsInStack);            
            }
            else
                error();
        break;
        case '+':
            if (!dstack.empty(itemsInStack))
            {
                operand1 = dstack.pop(itemsInStack);
                operand2 = dstack.pop(itemsInStack);
                result = operand1 + operand2;
                dstack.push(result, itemsInStack);                
            }
            else
                error();
        break;
        default:
            error();
        break;
    }
}

void error()
{
    std::cerr << "Error: Invalid expression." << endl;
    exit(1);
}

bool isOperator(char charCommand)
{
    if (charCommand == '/' || charCommand == '*' || 
        charCommand == '-' || charCommand == '+' ||
        charCommand == '^')
        return true;
    else
        return false;
}