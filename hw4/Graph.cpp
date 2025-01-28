#include <string>
#include <iostream>
#include "Graph.h"
using namespace std;
Graph::Graph(){

}
Graph::Graph(int row, int col, int**&fileArr){
    rowSize = row;
    colSize = col;
    size = row*col;
    graph = new Cubicle[size];
    int count = 0;
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            graph[count++].setIndex(i,j);
            if(j < colSize-1 && fileArr[i][j+1] % 2 == 0){
                this->addAdjacent(i,j,i,j+1);
            }
            if(i < rowSize-1 && fileArr[i][j] < 2){
                this->addAdjacent(i,j,i+1,j);
            }
        }
    }
}
Graph::~Graph(){
    Cubicle* cur;
    Cubicle* temp;
    for(int i = 0; i < size; i++){
        cur = graph[i].getNext();
        while(cur != nullptr){
            temp = cur;
            cur = cur->getNext();
            delete temp;
            //cout<<temp->toString();
        }
    } 
    delete[] graph;
    graph = nullptr;
}
void Graph::addAdjacent(const int row1, const int col1, const int row2, const int col2){

    int cub1Index = row1*(colSize)+ col1;
    int cub2Index = row2*(colSize)+ col2;
    Cubicle* curr = graph+cub1Index;
    curr->increaseAdjNum();
    while (curr->getNext() != nullptr) {
        curr = curr->getNext();
    }
    Cubicle* cub = new Cubicle(row2,col2);
    curr->setNext(cub); 
    curr = graph+cub2Index;
    curr->increaseAdjNum();
    while (curr->getNext() != nullptr) {
        curr = curr->getNext();
    }
    cub = new Cubicle(row1,col1);
    curr->setNext(cub);
}
Cubicle* Graph::getCubicle( const int x, const int y) const{
    return graph+(x*(colSize)+ y);
}
Cubicle* Graph::getCubicle(Cubicle* cub){
    if(cub == nullptr){
        return nullptr;
    }
    for (int i = 0; i < size; i++){
        if(graph[i].equals(*cub)){
            return graph+i;
        }
    }
    return nullptr;
    
}
void Graph::clearVisits(){
    for (int i = 0; i < size; i++){
        graph[i].setVisited(false);
    }
}
bool Graph::isVisited(Cubicle* cub){
    return getCubicle(cub)->getVisited();
}
void Graph::setVisited(Cubicle* cub, bool b){
    return getCubicle(cub)->setVisited(b);
}
Cubicle* Graph::getNextAdjacent(Cubicle* head){
    Cubicle* cur = head;
    for(int i = 0; i < head->getAdjNum(); i++){
        cur = cur->getNext();
        if(i == head->getIterator()){
            head->increaseIterator();
            if(cur != nullptr && !isVisited(cur)){
                return cur;
            }
        }
        head->checkIterator();
    }
    return nullptr;
}
void Graph::printAdjacentCubicles(const int row, const int col) const{
    Cubicle* cur = getCubicle(row,col);
    cout<<cur->toString()<<" -> ";
    while(cur->getNext() != nullptr){
        cur = cur->getNext();
        cout<<cur->toString();
        if(cur->getNext() != nullptr){
            cout<<",";
        }
    }
    cout<<endl;       
}

void Graph::printGraph() const{
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
           printAdjacentCubicles(i,j);
        }
    }
}
void Graph::printAllCubicles() const{
    int count = 0;
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            if(j != colSize-1){
                cout<<(graph[count++].toString())<<",";
            }
            else{
                cout<<(graph[count++].toString())<<endl;
            }
        }
    }
}