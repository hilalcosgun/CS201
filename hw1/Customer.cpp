#include <iostream>
using namespace std;
#include "Customer.h"

Customer::Customer(){
    customerID = 0;
    name = "";
}
Customer::Customer(const int customerID, const string name){
    this->customerID = customerID;
    this->name = name;
}

string Customer::toString(){
    return "Customer: " + to_string(customerID) + ", Name: " + name + ", DVDs Rented: " + to_string(DVDlist.getSize());
}
int Customer::getCustomerID(){
    return customerID;
}
string Customer::getName(){
    return name;
}
DVDArray& Customer::getDVDlist(){
    return DVDlist;
}
Customer& Customer::operator=(const Customer& right){
    if(right.customerID != customerID){
        customerID = right.customerID;
        name = right.name;
        int size = right.DVDlist.getSize();
        DVDlist = DVDArray(size);
        for(int i = 0; i < size; i++){
            DVDlist[i] = right.DVDlist[i];
        }
    }
    return *this;
}