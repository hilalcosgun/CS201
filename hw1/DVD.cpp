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
    this->isAvailable = "Available";
}

string DVD::toString(){
    return "DVD: " +  serialNo + ", Title: " + title + ", Director: " + director + ", " + isAvailable;
}
string DVD::getSerialNo(){
    return serialNo;
}
string DVD::getTitle(){
    return title;
}
string DVD::getDirector(){
    return director;
}
string DVD::getAvailability(){
    return isAvailable;
}
void DVD::setAvailability(const string availability){
    isAvailable = availability;
}