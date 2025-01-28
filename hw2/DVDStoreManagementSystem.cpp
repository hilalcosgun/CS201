//Hilal Coşgun 
//Sec2
//22201571
#include <iostream>
using namespace std;
#include "DVDStoreManagementSystem.h"

DVDStoreManagementSystem::DVDStoreManagementSystem(){
    customerList = nullptr;
    transactionHist = nullptr;
    DVDList = nullptr;
    customerNum = 0;
    transactionNum = 0;
    DVDNum = 0;
}
DVDStoreManagementSystem::~DVDStoreManagementSystem(){
    if(customerList){
        delete[] customerList;
    }
    if(transactionHist){
        delete[] transactionHist;
    }
    if(DVDList){
        delete[] DVDList;
    }
}
void DVDStoreManagementSystem::addDVD( const string serialNo, const string title, const string director ){
    if(findDVD(serialNo) == -1){
        if(DVDNum == 0){
            DVDList = new DVD[1];
            DVDList[0] = DVD(serialNo,title,director);
        }
        else{
            DVD* temp = DVDList;
            DVDList = new DVD[DVDNum+1];
            for(int i = 0; i < DVDNum; i++){
                DVDList[i] = temp[i];
            }
            DVDList[DVDNum] = DVD(serialNo,title,director);
            delete[] temp;
        }
        DVDNum++;
        cout<<"DVD with serial number " << serialNo << " successfully added." <<endl;
    }
    else{
        cout<<"Cannot add DVD. DVD with serial number "<< serialNo <<" already exists." <<endl;
    }
} 
void DVDStoreManagementSystem::removeDVD( const string serialNo ){
    int DVDIndex = findDVD(serialNo);
    if(DVDIndex == -1){
        cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" not found." <<endl;
    }
    else{
        if(DVDList[DVDIndex].getAvailability() == 0){
            cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" is currently rented by a customer."<<endl;
        }
        else{
            if(DVDNum == 1){
                delete[] DVDList;
                DVDList = nullptr;
            }
            else{
                int removedIndex = findDVD(serialNo);
                DVD* temp = DVDList;
                DVDList = new DVD[DVDNum-1];
                int index = 0;
                for(int i = 0; i < DVDNum; i++){
                    if(i != removedIndex){
                        DVDList[index++] = temp[i];
                    }
                }
                delete[] temp;
                cout<<"DVD with serial number " << serialNo << " successfully removed." <<endl;
            }
            DVDNum--;
        }
        
    }
}

void DVDStoreManagementSystem::addCustomer( const int customerID, const string name ){
    if(customerNum == 0){
        customerList = new Customer[1];
        customerList[0] = Customer(customerID, name);
        cout<<"Customer with ID " << customerID << " successfully added." <<endl; 
        customerNum++;
    }
    else{
        int cusIndex = findCustomer(customerID);
        if(cusIndex == -1){
            Customer* temp = customerList;
            customerList = new Customer[customerNum+1];
            for(int i = 0; i < customerNum; i++ ){
                customerList[i] = temp[i];
            }
            customerList[customerNum] = Customer(customerID, name);
            delete[] temp;
            customerNum++;
            cout<<"Customer with ID " << customerID << " successfully added." <<endl; 
        }
        else{
            cout<<"Cannot add customer. Customer with ID "<< customerID << " already exists." <<endl;
        }
    }                
}

void DVDStoreManagementSystem::removeCustomer( const int customerID ){
    int cusIndex = findCustomer(customerID);
    if(cusIndex == -1){
        cout<<"Cannot remove customer. Customer with ID "<< customerID << " not found." <<endl;
    }
    else{
        if(customerList[cusIndex].getDVDSize() == 0){
            if(customerNum == 1){
                delete[] customerList;
                customerList = nullptr;
            }
            else{
                Customer* temp = customerList;
                customerList = new Customer[customerNum-1];
                int index = 0;
                for(int i = 0; i < customerNum; i++){
                    if(i != cusIndex){
                        customerList[index++] = temp[i];
                    }
                }
                delete[] temp;
            }
            customerNum--;
            cout<<"Customer with ID "<< customerID <<" successfully removed."<<endl;
        }
        else{
            cout<<"Cannot remove customer. Customer with ID "<< customerID <<" has rented DVDs." <<endl;
        }
    }
}
void DVDStoreManagementSystem::rentDVD(  const int customerID, const string serialNo ){
    int cusIndex = findCustomer(customerID);
    int DVDIndex = findDVD(serialNo);
    if(DVDIndex == -1 && cusIndex == -1){
        cout<<"Cannot rent DVD. Customer with ID "<< customerID <<" and DVD with serial number "<< serialNo <<" not found."<<endl;

    }
    else if(DVDIndex == -1){
        cout<<"Cannot rent DVD. DVD with serial number "<< serialNo <<" not found."<<endl;
    }
    else if(cusIndex == -1){
        cout<<"Cannot rent DVD. Customer with ID "<< customerID <<" not found."<<endl;
    }
    else{
        if(DVDList[DVDIndex].getAvailability() == 0 ){
            cout<<"Cannot rent DVD. DVD with serial number "<< serialNo <<" is not available."<<endl;
        }
        else{
            DVDList[DVDIndex].setAvailability(0);
            int size = customerList[cusIndex].getDVDSize();
            if(size == 0){
                customerList[cusIndex].getDVDList() = new DVD[1];
                customerList[cusIndex].getDVDList()[0] = DVDList[DVDIndex];
            }
            else{
                DVD* temp = customerList[cusIndex].getDVDList();
                customerList[cusIndex].getDVDList() = new DVD[size+1];
                for(int i = 0; i < size; i++ ){
                    customerList[cusIndex].getDVDList()[i] = temp[i];
                }
                customerList[cusIndex].getDVDList()[size] = DVDList[DVDIndex];
                delete[] temp; 
            }
            customerList[cusIndex].setDVDSize(size+1);
            cout<<"DVD with serial number " << serialNo <<" successfully rented by customer with ID " << customerID << "." <<endl;
            addTransaction("Rental", customerID, serialNo);
        }
    }
}
void DVDStoreManagementSystem::returnDVD( const int customerID, const string serialNo){
    int cusIndex = findCustomer(customerID);
    int DVDIndex = findDVD(serialNo);
    if(DVDIndex == -1 && cusIndex == -1){
        cout<<"Cannot return DVD. Customer with ID "<< customerID <<" and DVD with serial number "<< serialNo <<" not found."<<endl;
    }
    else if(DVDIndex == -1){
        cout<<"Cannot return DVD. DVD with serial number "<< serialNo <<" not found."<<endl;
    }
    else if(cusIndex == -1){
        cout<<"Cannot return DVD. Customer with ID "<< customerID <<" not found."<<endl;
    }
    else{
        int size = customerList[cusIndex].getDVDSize();
        int removedIndex = -1;
        for(int i = 0; i < size; i++){
            if(customerList[cusIndex].getDVDList()[i].getSerialNo() == serialNo){
                removedIndex = i;
            }
        }
        if(removedIndex == -1){
            cout<<"Cannot return DVD. DVD with serial number "<< serialNo <<" not rented by customer with ID "<< customerID << "."<<endl;
        }
        else{
            DVDList[DVDIndex].setAvailability(1);
            if(size == 1){
                delete[] customerList[cusIndex].getDVDList();
                customerList[cusIndex].getDVDList() = nullptr;
            }
            else{
                DVD* temp = customerList[cusIndex].getDVDList();
                customerList[cusIndex].getDVDList() = new DVD[size-1];
                int index = 0;
                for(int i = 0; i < size; i++){
                    if(i != removedIndex){
                        customerList[cusIndex].getDVDList()[index++] = temp[i];
                    }
                }
                delete[] temp;
            }
            customerList[cusIndex].setDVDSize(size-1);
            cout<<"DVD with serial number " << serialNo <<" successfully returned by customer with ID " << customerID << "." <<endl;
            addTransaction("Return", customerID, serialNo);
        }
    }
}
void DVDStoreManagementSystem::showAllDVDs() const{
    cout<<"DVDs in the system:"<<endl;
    if(DVDNum == 0){
        cout<<"None"<<endl;
    }
    else{
        for(int i = 0; i < DVDNum; i++){
            cout<< DVDList[i].toString()<< endl;
        }
    }
}
void DVDStoreManagementSystem::showAllCustomers() const{
    cout<<"Customers in the system:"<<endl;
    if(customerNum == 0){
        cout<<"None"<<endl;
    }
    else{
        for(int i = 0; i < customerNum; i++){
            cout<< customerList[i].toString()<< endl;
        }
    }
}
void DVDStoreManagementSystem::showDVD( const string serialNo ) const{
    int DVDIndex = findDVD(serialNo);
    if(DVDIndex == -1){
        cout<<"DVD with serial number "<< serialNo <<" not found."<<endl;
    }
    else{
        cout<< DVDList[DVDIndex].toString() <<endl;
    }
}
void DVDStoreManagementSystem::showCustomer( const int customerID ) const{
    int cusIndex = findCustomer(customerID);
    if(cusIndex == -1){
        cout<<"Customer with ID "<< customerID <<" not found."<<endl;
    }
    else{
        cout<< customerList[cusIndex].toString() <<endl;
    }
}
void DVDStoreManagementSystem::showTransactionHistory() const{
    cout<<"Transactions in the system:"<<endl;
    if(transactionNum == 0){
        cout<<"None"<<endl;
    }
    else{
        for(int i = 0; i < transactionNum; i++){
            cout<< transactionHist[i].toString()<< endl;
        }
    }    
}
int DVDStoreManagementSystem::findCustomer(const int customerID) const{
    if(customerNum > 0 ){
        for(int i = 0; i < customerNum; i++){
            if(customerList[i].getCustomerID() == customerID){
                return i;
            }
        }
    }
    return -1;
}

void DVDStoreManagementSystem::addTransaction(const string transaction, const int customerID, const string serialNo){
    if(transactionNum == 0){
        transactionHist = new Transaction[++transactionNum];
        transactionHist[0] = Transaction(transaction, customerID, serialNo);
    }
    else{
        Transaction* temp = transactionHist;
        transactionHist = new Transaction[transactionNum+1];
        for(int j = 0; j < transactionNum; j++ ){
            transactionHist[j] = temp[j];
        }
        transactionHist[transactionNum] = Transaction(transaction, customerID, serialNo);
        transactionNum++;
        delete[] temp;
    }
}
void DVDStoreManagementSystem::showCustomerDVD(int cusIndex){
    
        cout<< customerList[cusIndex].getDVDSize();
        //cout<<customerList[cusIndex].getDVDlist()[i].toString();


}
int DVDStoreManagementSystem::findDVD(const string serialNo)const{
    if(DVDNum > 0){
        for(int i = 0; i < DVDNum; i++){
            if(DVDList[i].getSerialNo() == serialNo){
                return i;
            }
        }
    }
    return -1;
}