#ifndef BUILDINGMAP_H
#define BUILDINGMAP_H
#include <string>
#include <iostream>
#include "Graph.h"
using namespace std;
class BuildingMap {
    public:
        BuildingMap(const string buildingMapFile);
        ~BuildingMap();
        void displayAllCubicles() const;
        void displayAdjacentCubicles(const int row, const int col) const;
        void displayBuildingMap() const;
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
        const int avoidRow, const int avoidCol);
        
    private:
        Graph* buildingGraph;
        void findPathsGeneral(const int startRow, const int startCol, const int endRow, const int endCol);
};
#endif