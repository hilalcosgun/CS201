//Hilal Coşgun 22201571 Section:2
#include "BiologicalPathway.h"
#include <iostream>
#include <string>

using namespace std;

BiologicalPathway::BiologicalPathway(){
    pathwayListHeader = nullptr;
    pathwayCount = 0;
}
BiologicalPathway::~BiologicalPathway(){
    while(pathwayListHeader != nullptr){
         removeFirstPathway();
    }
}

void BiologicalPathway::addPathway( const int pathwayId, const string pathwayName ){
    if(findPathway(pathwayId) != nullptr){
        cout<<"Cannot add pathway. There is already a pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }
    if(pathwayListHeader == nullptr ){
        pathwayListHeader = new NodePathway(pathwayId,pathwayName);
        pathwayCount++;
        cout<<"Added pathway "<<pathwayId<<"."<<endl;
        return;
    }
    if(pathwayId < pathwayListHeader->getID()){
        NodePathway* newNode = new NodePathway(pathwayId,pathwayName);
        newNode->setNext(pathwayListHeader);
        pathwayListHeader = newNode;
        pathwayCount++;
        cout<<"Added pathway "<<pathwayId<<"."<<endl;
        return;    
    }
    for(NodePathway* curPtr = pathwayListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        
        if(curPtr->getNext() == nullptr || curPtr->getNext()->getID() > pathwayId){
            NodePathway* newNode = new NodePathway(pathwayId,pathwayName);
            newNode->setNext(curPtr->getNext());
            curPtr->setNext(newNode);
            pathwayCount++;
            cout<<"Added pathway "<<pathwayId<<"."<<endl;
            return;
        }
    } 
} 

void BiologicalPathway::removePathway( const int pathwayId ){
    if(findPathway(pathwayId) == nullptr ){
        cout<<"Cannot remove pathway. There is no pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }
    if(pathwayListHeader->getID() == pathwayId){
        if(pathwayCount == 1){
            delete pathwayListHeader;
            pathwayListHeader = nullptr;
        }
        else{
            NodePathway* temp = pathwayListHeader->getNext();
            delete pathwayListHeader;
            pathwayListHeader = temp;
        }
        pathwayCount--;
        cout<<"Removed pathway "<<pathwayId<<"."<<endl;
        return;
    }
    for(NodePathway* curPtr = pathwayListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getNext() != nullptr && curPtr->getNext()->getID() == pathwayId){
            NodePathway* temp = curPtr->getNext()->getNext();
            delete curPtr->getNext();
            curPtr->setNext(temp);
            pathwayCount--;
            cout<<"Removed pathway "<<pathwayId<<"."<<endl;
            return;
        }
    }
}

void BiologicalPathway:: printPathways() const{
    if(pathwayCount==0){
        cout<<"There are no pathways to show."<<endl;
        return;
    }
    cout<<"Pathways in the system:"<<endl;
    for(NodePathway* curPtr = pathwayListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        cout<<"Pathway "<<curPtr->getID()<<" : "<<curPtr->getName()<<" ("<<curPtr->getProteinCount()<<" Proteins)"<<" ("
        <<curPtr->getTotalGenCount()<<" Genes)"<<endl;
    } 
}

void BiologicalPathway::addProtein( const int proteinId, const int pathwayId ){
    if(findPathway(pathwayId) == nullptr){
        cout<<"Cannot add protein. There is no pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }
    for(NodePathway* curPtr = pathwayListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->findProtein(proteinId) != nullptr){
            cout<<"Cannot add protein. There is a pathway having a protein with ID "<<proteinId<<"."<<endl;
            return;
        }  
    }
    NodePathway* pathPtr = findPathway(pathwayId);
    pathPtr->addProtein(proteinId);
    cout<<"Added protein "<<proteinId<<" to pathway "<<pathwayId<<"."<<endl;
}

void BiologicalPathway::removeProtein( const int proteinId, const int pathwayId ){
    NodePathway* pathPtr = findPathway(pathwayId);
    if(pathPtr == nullptr){
        cout<<"Cannot remove protein. There is no pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }
    if(pathPtr->findProtein(proteinId) == nullptr){
        cout<<"Cannot remove protein. Pathway "<<pathwayId<<" does not have a protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    pathPtr->removeProtein(proteinId);
    cout<<"Removed protein "<<proteinId<<" from pathway "<<pathwayId<<"."<<endl;
}

void BiologicalPathway::printProteinsInPathway( const int pathwayId ) const{
    NodePathway* pathPtr = findPathway(pathwayId);
    if(pathPtr == nullptr){
        cout<<"Cannot print proteins. There is no pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }
    if(pathPtr->getProteinCount() == 0){
        cout<<"There are no proteins to show in pathway "<<pathwayId<<"."<<endl;
        return;
    }
    cout<<"Proteins in pathway "<<pathwayId<<":"<<endl;
    for(NodeProtein* curPtr = pathPtr->getProteinListHeader(); curPtr!= nullptr; curPtr = curPtr->getNext()){
        cout<<"Protein ID : "<<curPtr->getID()<<", Gene IDs : "<< curPtr->printGenes()<<endl;
    }
}

void BiologicalPathway::addGene( const int geneID, const string geneName, const int proteinId ){
    NodeProtein* proteinPtr = nullptr;
    for(NodePathway* curPtr = pathwayListHeader; curPtr !=nullptr; curPtr = curPtr->getNext()){
        if(curPtr->findProtein(proteinId) != nullptr){
            proteinPtr = curPtr->findProtein(proteinId);
        }  
    }
    if(proteinPtr == nullptr){
        cout<<"Cannot add gene. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    for(NodePathway* pathPtr = pathwayListHeader; pathPtr !=nullptr; pathPtr = pathPtr->getNext()){
        for(NodeProtein* proPtr = pathPtr->getProteinListHeader(); proPtr != nullptr; proPtr = proPtr->getNext()){
            if(proPtr->findGen(geneID) !=nullptr){
                cout<<"Cannot add gene. Gene "<<geneID<<" is already in use."<<endl;
                return;
            }
        }
    }
    proteinPtr->addGen(geneID, geneName);
    cout<<"Added gene "<<geneID<<" to protein "<<proteinId<<"."<<endl;
}

void BiologicalPathway::removeGene( const int geneID, const int proteinId ){
    NodeProtein* proteinPtr = nullptr;
    for(NodePathway* curPtr = pathwayListHeader ;curPtr !=nullptr; curPtr = curPtr->getNext()){
        if(curPtr->findProtein(proteinId) != nullptr){
            proteinPtr = curPtr->findProtein(proteinId);
        }  
    }
    if(proteinPtr == nullptr){
        cout<<"Cannot remove gene. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    if(proteinPtr->findGen(geneID) == nullptr){
        cout<<"Cannot remove gene. There is no gene "<<geneID<<" encoding protein "<<proteinId<<"."<<endl;
        return;
    }
    proteinPtr->removeGen(geneID);
    cout<<"Removed gene "<<geneID<<" from protein "<<proteinId<<"."<<endl;
}

void BiologicalPathway::printGenesOfProtein( const int proteinId ) const{
    NodeProtein* proteinPtr = nullptr;
    for(NodePathway* curPtr = pathwayListHeader ;curPtr !=nullptr; curPtr = curPtr->getNext()){
        if(curPtr->findProtein(proteinId) != nullptr){
            proteinPtr = curPtr->findProtein(proteinId);
        }  
    }
    if(proteinPtr == nullptr){
        cout<<"Cannot print genes. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    if(proteinPtr->getGenCount()==0){
        cout<<"There are no genes to show in protein "<<proteinId<<"."<<endl;
        return;
    }
    cout<<"Genes in protein "<<proteinId<<":"<<endl;
    for(NodeGen* genPtr = proteinPtr->getGenListHeader(); genPtr != nullptr; genPtr = genPtr->getNext()){
        cout<<"GENE "<<genPtr->getID()<<" : "<<genPtr->getName()<<endl;
    }

}
NodePathway* BiologicalPathway::findPathway(const int pathwayID) const{
    if(pathwayListHeader == nullptr){
        return nullptr;
    }
    if(pathwayID < pathwayListHeader->getID()){
        return nullptr;
    }
    for(NodePathway* curPtr = pathwayListHeader; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getID() == pathwayID){
            return curPtr;
        }
        if(curPtr->getID() > pathwayID){
            return nullptr;
        }
    }
    return nullptr;
}

void BiologicalPathway::removeFirstPathway(){
    NodePathway* curPtr = pathwayListHeader;
    pathwayListHeader = pathwayListHeader->getNext();
    delete curPtr;
    curPtr = nullptr;
    pathwayCount--;
}



    

