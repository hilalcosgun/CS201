//Hilal Coşgun 22201571 Section:2
#include "NodeProtein.h"
#include <iostream>
#include <string>
using namespace std;

NodeProtein::NodeProtein(const int id){
    ID = id;
    next = nullptr;
    genListHeader = nullptr;
    genCount = 0;
}

NodeProtein::~NodeProtein(){
    while(genListHeader != nullptr){
        removeFirstGene();
    }
}
int NodeProtein::getGenCount()const{
    return genCount;
}
int NodeProtein::getID() const{
    return ID;
}

void NodeProtein::setID(const int id){
    ID = id;
}
NodeProtein*NodeProtein::getNext() const{
    return next;
}
NodeGen* NodeProtein::getGenListHeader() const{
    return genListHeader;
}
void NodeProtein::setNext(NodeProtein* nextNode){
    next = nextNode;
}

void NodeProtein::addGen(const int genId, const string genName){
    if(genListHeader == nullptr ){
        genListHeader = new NodeGen(genId,genName);
        genCount++;
        return;
    }
    if(genId < genListHeader->getID()){
        NodeGen* newNode = new NodeGen(genId,genName);
        newNode->setNext(genListHeader);
        genListHeader = newNode;
        genCount++;
        return;    
    }
    for(NodeGen* curPtr = genListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getNext() == nullptr || curPtr->getNext()->getID() > genId){
            NodeGen* newNode = new NodeGen(genId,genName);
            newNode->setNext(curPtr->getNext());
            curPtr->setNext(newNode);
            genCount++;
            return;
        }
    }
}
void NodeProtein::removeGen(const int geneID){
    //gen is in the protein, already checked.
    if(genListHeader->getID() == geneID){
        if(genCount == 1){
            delete genListHeader;
            genListHeader = nullptr;
        }
        else{
            NodeGen* temp = genListHeader->getNext();
            delete genListHeader;
            genListHeader = temp;
        }
        genCount--;
        return;
    }
    for(NodeGen* curPtr = genListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getNext() != nullptr && curPtr->getNext()->getID() == geneID){
            NodeGen* temp = curPtr->getNext()->getNext();
            delete curPtr->getNext();
            curPtr->setNext(temp);
            genCount--;
            return;
        }
    }
}

string NodeProtein::printGenes()const{
    if(genCount == 0){
        return"None";
    }
    string genes = "["; 
    NodeGen* curPtr;
    for(curPtr = genListHeader; curPtr->getNext() != nullptr; curPtr = curPtr->getNext()){
        genes += to_string(curPtr->getID()) + ", ";
    }
    genes += to_string(curPtr->getID()) + "]";
    return genes;

}

NodeGen* NodeProtein::findGen(const int genID) const{
    if(genListHeader == nullptr){
        return nullptr;
    }
    if(genID < genListHeader->getID()){
        return nullptr;
    }
    for(NodeGen* curPtr = genListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getID() == genID){
            return curPtr;
        }
        if(curPtr->getID() > genID){
            return nullptr;
        }
    }
    return nullptr;
}
void NodeProtein::removeFirstGene(){
    NodeGen* curPtr = genListHeader;
    genListHeader = genListHeader->getNext();
    delete curPtr;
    curPtr = nullptr;
    genCount--;
}