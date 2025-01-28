//Hilal Coşgun 
//Sec2
//22201571
#ifndef _TRANSACTION_H
#define _TRANSACTION_H
#include <string>
using namespace std;
class Transaction
{
private:
    string action;
    int customerID;
    string serialNo; 
    
public:
    Transaction();
    Transaction(const string action,const int customerID, const string serialNo );
    string getAction()const;
    int getCustomerID()const;
    string getSerialNo()const;
    string toString()const;
};
#endif
