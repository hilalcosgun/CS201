
#include <iostream>
#include <string>
#include "Cubicle.h"
Cubicle::Cubicle(){
    x = -1;
    y = -1;
    adjNum = 0;
    iterator = 0;
    isVisited = false;
    next = nullptr;
}
Cubicle::Cubicle(int Indx, int Indy){
    x = Indx;
    y = Indy;
    adjNum = 0;
    iterator = 0;
    isVisited = false;
    next = nullptr;
}
Cubicle::~Cubicle(){
    next = nullptr;
}
void Cubicle::setIndex(int Indx, int Indy){
    x = Indx;
    y = Indy;
}
string Cubicle::toString(){
    return "("+ to_string(x) +"," + to_string(y)+ ")";
}
bool Cubicle::equals(Cubicle& cub){
    if(cub.x == x & cub.y == y){
        return true;
    }
    return false;
}
Cubicle *Cubicle::getNext()
{
    return next;
}
void Cubicle::setNext(Cubicle* adjacent){
    next = adjacent;
}
bool Cubicle::getVisited() const{
    return isVisited;
}
void Cubicle::setVisited(bool b){
    isVisited = b;
}
int Cubicle::getAdjNum(){
    return adjNum;
}
void Cubicle::increaseAdjNum(){
    adjNum = adjNum + 1;
}
int Cubicle::getIterator(){
    return iterator;
}
void Cubicle::increaseIterator(){
    iterator = iterator + 1;
    
}
void Cubicle::checkIterator(){
    if(iterator >= adjNum){
        iterator = 0;
    }
}
