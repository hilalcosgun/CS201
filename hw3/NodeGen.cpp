//Hilal Coşgun 22201571 Section:2
#include "NodeGen.h"
#include <iostream>
#include <string>

using namespace std;

NodeGen::NodeGen(const int id, const string Name){
    ID = id;
    name = Name;
    next = nullptr;
}
NodeGen::~NodeGen(){
    
}
int NodeGen::getID() const{
    return ID;
} 
string NodeGen::getName() const{
    return name;
}
NodeGen* NodeGen::getNext() const{
    return next;
}
void NodeGen::setID(const int id){
    ID = id;
}
void NodeGen::setNext(NodeGen* nextNode){
    next = nextNode;
}