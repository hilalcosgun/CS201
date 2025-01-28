//Hilal Coşgun 
//Sec2
//22201571
#ifndef _CUSTOMER_H
#define _CUSTOMER_H
#include <string>
#include "DVD.h"
using namespace std; 
class Customer{
private:
    int customerID;
    string name;
    DVD* DVDlist;
    int DVDSize;
public:
    Customer();
    Customer(const int customerID, const string name);
    ~Customer();
    string toString() const;
    int getCustomerID() const;
    int getDVDSize()const;
    void setDVDSize( int newSize);
    string getName() const;
    DVD*& getDVDList();
    Customer& operator=(const Customer& right);
    DVD& operator[](int ind) const;
};
#endif