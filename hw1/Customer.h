#include <string>
#include "DVDArray.h"
using namespace std; 
class Customer{
private:
    int customerID;
    string name;
    DVDArray DVDlist;
public:
    Customer();
    Customer(const int customerID, const string name);
    string toString();
    int getCustomerID();
    string getName();
    DVDArray& getDVDlist();
    Customer& operator=(const Customer& right);
};