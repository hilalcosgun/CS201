//Hilal Coşgun 22201571 Section:2
#include "NodePathway.h"
#include <iostream>
#include <string>

using namespace std;

NodePathway::NodePathway(const int id, const string Name){
    ID = id;
    name = Name;
    proteinCount = 0;
    next = nullptr;
    proteinListHeader = nullptr;
}
NodePathway::~NodePathway(){
    while(proteinListHeader != nullptr){
        removeFirstProtein();
    }
}
int NodePathway::getID() const{
    return ID;
} 
string NodePathway::getName() const{
    return name;
}

NodeProtein* NodePathway:: getProteinListHeader() const{
    return proteinListHeader;
}
int NodePathway::getProteinCount() const{
    return proteinCount;
}
int NodePathway::getTotalGenCount() const{
    int totalGenCount = 0;
    for(NodeProtein* curptr = proteinListHeader; curptr != nullptr; curptr = curptr->getNext()){
        totalGenCount += curptr->getGenCount();
    }
    return totalGenCount;
}

NodePathway* NodePathway::getNext() const{
    return next;
}
void NodePathway::setID(const int id){
    ID = id;
}
void NodePathway::setName(const string Name){
    name = Name;
}
void NodePathway::setNext (NodePathway* nextNode){
    next = nextNode;
}

void NodePathway::addProtein(const int proteinId) {
    if(proteinListHeader == nullptr ){
        proteinListHeader = new NodeProtein(proteinId);
        proteinCount++;
        return;
    }
    if(proteinId < proteinListHeader->getID()){
        NodeProtein* newNode = new NodeProtein(proteinId);
        newNode->setNext(proteinListHeader);
        proteinListHeader = newNode;
        proteinCount++;
        return;    
    }
    for(NodeProtein* curPtr = proteinListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getNext() == nullptr || curPtr->getNext()->getID() > proteinId){
            NodeProtein* newNode = new NodeProtein(proteinId);
            newNode->setNext(curPtr->getNext());
            curPtr->setNext(newNode);
            proteinCount++;
            return;
        }
    }
}
void NodePathway::removeProtein(const int proteinId){
    //protein is in the pathway, already checked.
    if(proteinListHeader->getID() == proteinId){
        if(proteinCount == 1){
            delete proteinListHeader;
            proteinListHeader = nullptr;
        }
        else{
            NodeProtein* temp = proteinListHeader->getNext();
            delete proteinListHeader;
            proteinListHeader = temp;
        }
        proteinCount--;
        return;
    }
    for(NodeProtein* curPtr = proteinListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getNext() != nullptr && curPtr->getNext()->getID() == proteinId){
            NodeProtein* temp = curPtr->getNext()->getNext();
            delete curPtr->getNext();
            curPtr->setNext(temp);
            proteinCount--;
            return;
        }
    }
}

NodeProtein* NodePathway::findProtein(const int proteinID) const{
    if(proteinListHeader == nullptr){
        return nullptr;
    }
    if(proteinID < proteinListHeader->getID()){
        return nullptr;
    }
    for(NodeProtein* curPtr = proteinListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getID() == proteinID){
            return curPtr;
        }
        if(curPtr->getID() > proteinID){
            return nullptr;
        }
    }
    return nullptr;
}

void NodePathway::removeFirstProtein(){
    NodeProtein* curPtr = proteinListHeader;
    proteinListHeader = proteinListHeader->getNext();
    delete curPtr;
    curPtr = nullptr;
    proteinCount--;
}