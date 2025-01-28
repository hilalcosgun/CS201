#include <iostream>

using namespace std;

#include "DVDStoreManagementSystem.h"

DVDStoreManagementSystem::DVDStoreManagementSystem(){
    customerList = nullptr;
    transactionHist = nullptr;
    customerNum = 0;
    transactionNum = 0;
    
}
DVDStoreManagementSystem::~DVDStoreManagementSystem(){
    if(customerList){
        delete[] customerList;
    }
    if(transactionHist){
        delete[] transactionHist;
    }
}
void DVDStoreManagementSystem::addDVD( const string serialNo, const string title, const string director ){
    if(DVDList.addDVD(DVD(serialNo,title,director)) == 0){
        cout<<"DVD with serial number " << serialNo << " successfully added." <<endl;
    }
    else{
        cout<<"Cannot add DVD. DVD with serial number "<< serialNo <<" already exists." <<endl;
    }
    /*if(DVDList.findDVD() == -1){
        int size = DVDList.getSize();
        DVDArray temp = DVDList;
        DVDList = new DVDArray[size+1];
        for(int i = 0; i < size; i++){
            DVDList[i] = temp[i];
        }
        DVDList[size] = DVD(serialNo, title, director);
        delete[] temp;
        cout<<"Customer with serial number " << serialNo << " successfully added." <<endl;
    }
    else{
        cout<<"Cannot add DVD. DVD with serial number "<< serialNo <<" already exists." <<endl;
    }*/
}  
void DVDStoreManagementSystem::removeDVD( const string serialNo ){
    if(DVDList.findDVD(serialNo) == -1){
        cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" not found." <<endl;
    }
    else{
        int removedIndex = DVDList.findDVD(serialNo);
        if(DVDList[removedIndex].getAvailability() == "Available"){
            DVDList.removeDVD(removedIndex);
            cout<<"DVD with serial number "<< serialNo <<" successfully removed."<<endl;
        }
        else{
            cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" is currently rented by a customer." <<endl;
        }
    }
}

void DVDStoreManagementSystem::addCustomer( const int customerID, const string name ){
    if(customerNum == 0){
        customerList = new Customer[++customerNum];
        customerList[0] = Customer(customerID, name);
        cout<<"Customer with ID " << customerID << " successfully added." <<endl; 
    }
    else{
        int cusIndex = findCustomer(customerID);
        if(cusIndex == -1){
            Customer* temp = customerList;
            customerList = new Customer[customerNum+1];
            for(int j = 0; j < customerNum; j++ ){
                customerList[j] = temp[j];
            }
            customerList[customerNum] = Customer(customerID, name);
            customerNum++;
            delete[] temp;
            cout<<"Customer with ID " << customerID << " successfully added." <<endl; 
        }
        else{
            cout<<"Cannot add customer. Customer with ID "<< customerID << " already exists." <<endl;
        }
    }                
}


void DVDStoreManagementSystem::removeCustomer( const int customerID ){
    for(int i = 0; i < customerNum; i++){
        if(customerList[i].getCustomerID() == customerID){
            if(customerList[i].getDVDlist().getSize() == 0){
                Customer* temp = customerList;
                customerList = new Customer[customerNum-1];
                int index = 0;
                for(int j = 0; j < customerNum; j++){
                    if(j != i){
                        customerList[index++] = temp[j];
                    }
                }
                customerNum--;
                delete[] temp;
                cout<<"Customer with ID "<< customerID <<" successfully removed."<<endl;
            }
            else{
                cout<<"Cannot remove customer. Customer with ID "<< customerID <<" has rented DVDs." <<endl;
            }
            return;
        }
    }
    cout<<"Cannot remove customer. Customer with ID "<< customerID << " not found." <<endl;
}
void DVDStoreManagementSystem::rentDVD(  const int customerID, const string serialNo ){
    int cusIndex = findCustomer(customerID);
    int DVDIndex = DVDList.findDVD(serialNo);
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
        if(DVDList[DVDIndex].getAvailability() == "Rented" ){
            cout<<"Cannot rent DVD. DVD with serial number "<< serialNo <<" is not available."<<endl;
        }
        else{
            DVDList[DVDIndex].setAvailability("Rented");
            customerList[cusIndex].getDVDlist().addDVD(DVDList[DVDIndex]);
            cout<<"DVD with serial number " << serialNo <<" successfully rented by customer with ID " << customerID << "." <<endl;
            addTransaction("Rental", customerID, serialNo);
        }
    }
}
void DVDStoreManagementSystem::returnDVD( const int customerID, const string serialNo){
    int cusIndex = findCustomer(customerID);
    int DVDIndex = DVDList.findDVD(serialNo);
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
        if(customerList[cusIndex].getDVDlist().findDVD(serialNo) == -1 ){
            cout<<"Cannot return DVD. DVD with serial number "<< serialNo <<" not rented by customer with ID "<< customerID << "."<<endl;
        }
        else{
            DVDList[DVDIndex].setAvailability("Available");
            customerList[cusIndex].getDVDlist().removeDVD(DVDIndex);
            cout<<"DVD with serial number " << serialNo <<" successfully returned by customer with ID " << customerID << "." <<endl;
            addTransaction("Return", customerID, serialNo);
        }
    }
}
void DVDStoreManagementSystem::showAllDVDs() const{
    cout<<"DVDs in the system:"<<endl;
    if(DVDList.getSize() == 0){
        cout<<"None"<<endl;
    }
    else{
        for(int i = 0; i < DVDList.getSize(); i++){
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
    int DVDIndex = DVDList.findDVD(serialNo);
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
int DVDStoreManagementSystem::findCustomer(const int customerID)const{
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
    //for(int i = 0; i <  ; i++){
        cout<<customerList[cusIndex].getDVDlist().getSize();
        //cout<<customerList[cusIndex].getDVDlist()[i].toString();
    //}

}