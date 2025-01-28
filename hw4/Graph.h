#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include "Cubicle.h"
using namespace std;
class Graph{
    private:
        int rowSize;
        int colSize;
        int size;
        Cubicle* graph;
        void addAdjacent(int row1, int col1, int row2, int col2);
    public:
        Graph();
        ~Graph();
        Graph(int row, int col,  int**&fileArr);
        Cubicle* getCubicle(Cubicle* cub);
        Cubicle* getCubicle(const int x, const int y) const;
        void clearVisits();
        bool isVisited(Cubicle* cub);
        void setVisited(Cubicle* cub, bool b);
        Cubicle*getNextAdjacent( Cubicle* head);
        void printGraph() const;
        void printAllCubicles() const;
        void printAdjacentCubicles(const int row, const int col) const;

};
#endif
