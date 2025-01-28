#include <string>
#include <iostream>
#include <fstream> 
#include "BuildingMap.h"
#include "CubicleStack.h"
using namespace std;
BuildingMap::BuildingMap(const string buildingMapFile){
    int row, column;
    string line;
    ifstream file(buildingMapFile);
    if (!file.is_open()) {
        file.close(); 
        return; 
    }
    file>>row;
    file>>column;
    cout<<row<<" rows and "<<column<<" columns have been read."<<endl;
    getline(file,line);
    int** fileArr = new int*[row];
    for(int i = 0; i < row; i++){
        fileArr[i] = new int[column];
    }
    int i = 0;
    while (getline(file, line) && i < row){ 
        int j = 0;
        for (char num : line) {
            fileArr[i][j] = num - '0';
            j++;
        }
        i++;
    }
    buildingGraph = new Graph(row, column, fileArr);
    for(int i = 0; i< row; i++){
        delete[] fileArr[i];
    }
    delete[] fileArr;
}
BuildingMap::~BuildingMap(){
    delete buildingGraph;
}
void BuildingMap::findPathsGeneral(const int startRow, const int startCol, const int endRow, const int endCol){
    Cubicle* origin = (*buildingGraph).getCubicle(startRow,startCol);
    Cubicle* dest = (*buildingGraph).getCubicle(endRow,endCol);
    CubicleStack pathStack;
    Cubicle* cur;
    Cubicle* adj;
    bool found = false;
    pathStack.push(origin);
    (*origin).setVisited(true);
    while(!pathStack.isEmpty()){
        cur = &(pathStack.peek());
        adj = (*buildingGraph).getNextAdjacent(cur);

        if(adj == nullptr){
            (*buildingGraph).setVisited(cur,false);
            pathStack.pop();
        }
        else{
            pathStack.push((*buildingGraph).getCubicle(adj));
            (*buildingGraph).setVisited((*buildingGraph).getCubicle(adj),true);
            if(pathStack.peek().equals(*dest)){
                pathStack.printStack();
                found = true;
                (*buildingGraph).setVisited(&(pathStack.peek()),false);
                pathStack.pop();
            }
        }
    }
    if(!found){
        cout<<"None"<<endl;
    }
    (*buildingGraph).clearVisits();
}
void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol){
    Cubicle* origin = (*buildingGraph).getCubicle(startRow,startCol);
    Cubicle* dest = (*buildingGraph).getCubicle(endRow,endCol);
    cout<<"Paths from "<<origin->toString()<<" to "<<dest->toString()<<" are:"<<endl;
    findPathsGeneral(startRow,startCol,endRow,endCol);
} 
void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
        const int avoidRow, const int avoidCol){
            Cubicle* origin = (*buildingGraph).getCubicle(startRow,startCol);
            Cubicle* dest = (*buildingGraph).getCubicle(endRow,endCol);
            Cubicle* avoid = (*buildingGraph).getCubicle(avoidRow,avoidCol);
            cout<<"Paths from "<<origin->toString()<<" to "<<dest->toString()<<" avoiding "<<avoid->toString()<<" are:"<<endl;
            (*buildingGraph).setVisited(avoid,true);
            findPathsGeneral(startRow,startCol,endRow,endCol);
}
void BuildingMap::displayAllCubicles() const{
    cout<<"The cubicles in the building are:"<<endl;
    (*buildingGraph).printAllCubicles();
}
void BuildingMap::displayAdjacentCubicles(const int row, const int col) const{
    cout<<"The cubicles adjacent to "<<(*buildingGraph).getCubicle(row,col)->toString()<<" are:"<<endl;
    (*buildingGraph).printAdjacentCubicles(row,col);
}
void BuildingMap::displayBuildingMap() const{
    cout<<"The building map is as follows:"<<endl;
    (*buildingGraph).printGraph();
}
    

    



