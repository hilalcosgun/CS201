#include <iostream>
#include <string>
using namespace std;
#include "Transaction.h"

Transaction::Transaction(){
    transaction = "";
    customerID = -1;
    serialNo = "";
}
Transaction::Transaction(const string transaction, const int customerID, const string serialNo){
    this->transaction = transaction;
    this->customerID = customerID;
    this->serialNo = serialNo;
}
string Transaction::toString(){
    return "Transaction: " + transaction + ", Customer: " + std::to_string(customerID) + ", DVD: " + serialNo;
}