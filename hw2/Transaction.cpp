//Hilal Coşgun 
//Sec2
//22201571
#include <iostream>
#include <string>
using namespace std;
#include "Transaction.h"

Transaction::Transaction(){
    action = "";
    customerID = -1;
    serialNo = "";
}
Transaction::Transaction(const string action, const int customerID, const string serialNo){
    this->action = action;
    this->customerID = customerID;
    this->serialNo = serialNo;
}
string Transaction::toString()const{
    return "Transaction: " + action + ", Customer: " + std::to_string(customerID) + ", DVD: " + serialNo;
}
string Transaction::getAction()const{
    return action;
}
int Transaction::getCustomerID()const{
    return customerID;
}
string Transaction::getSerialNo()const{
    return serialNo;
}