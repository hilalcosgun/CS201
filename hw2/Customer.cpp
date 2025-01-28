//Hilal Coşgun 
//Sec2
//22201571
#include <iostream>
using namespace std;
#include "Customer.h"

Customer::Customer(){
    customerID = 0;
    name = "";
    DVDlist = nullptr;
    DVDSize = 0;
}
Customer::Customer(const int customerID, const string name){
    this->customerID = customerID;
    this->name = name;
    DVDlist = nullptr;
    DVDSize = 0;
}
Customer::~Customer(){
    if(DVDlist){
        delete[] DVDlist;
    }
}
string Customer::toString()const{
    return "Customer: " + to_string(customerID) + ", Name: " + name + ", DVDs Rented: " + to_string(DVDSize);
}
int Customer::getCustomerID()const{
    return customerID;
}
string Customer::getName()const{
    return name;
}
DVD*& Customer::getDVDList(){
    return DVDlist;
}
Customer& Customer::operator=(const Customer& right){
    if(right.customerID != customerID){
        customerID = right.customerID;
        name = right.name;
        if(DVDSize == right.DVDSize){
            for(int i = 0; i < DVDSize; i++){
                DVDlist[i] = right.DVDlist[i];
            }
        }
        else{
            DVDSize = right.DVDSize;
            delete[] DVDlist;
            DVDlist = new DVD[DVDSize];
            for(int i = 0; i < DVDSize; i++){
                DVDlist[i] = right.DVDlist[i];
            }
        }
    }
    return *this;
}
DVD& Customer::operator[](int ind) const{
    if(ind < 0 || ind >= DVDSize){
        throw out_of_range("Invalid index");
    }
    else{
        return DVDlist[ind];
    }
}

int Customer::getDVDSize()const{
    return DVDSize;
}
void Customer::setDVDSize(int newSize){
    DVDSize = newSize;
}