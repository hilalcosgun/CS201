//Hilal Coşgun 
//Sec2
//22201571
#include <iostream>
using namespace std;
#include "DVD.h"

DVD::DVD(){
    serialNo = "";
    title = "";
    director = "";
    isAvailable = false;
}
DVD::DVD(const string serialNo,const string title,const string director){
    this->serialNo = serialNo;
    this->title = title;
    this->director = director;
    this->isAvailable = 1;
}

string DVD::toString()const{
    string availability = "Available";
    if(!isAvailable){
        availability = "Rented";
    }
    return "DVD: " +  serialNo + ", Title: " + title + ", Director: " + director + ", " + availability;
}
string DVD::getSerialNo()const{
    return serialNo;
}
string DVD::getTitle()const{
    return title;
}
string DVD::getDirector()const{
    return director;
}
bool DVD::getAvailability()const{
    return isAvailable;
}
void DVD::setAvailability(const bool availability){
    isAvailable = availability;
}