#ifndef CUBICLE_H
#define CUBICLE_H
#include <string>
#include <iostream>
using namespace std;
class Cubicle{
    private:
        int x,y; 
        int adjNum;
        int iterator;
        bool isVisited;
        Cubicle* next;
    public:
        Cubicle();
        ~Cubicle();
        Cubicle(int Indx, int Indy);
        void setNext(Cubicle* adjacent);
        Cubicle* getNext();
        void setIndex(int Indx, int Indy);
        bool getVisited()const;
        void setVisited(bool b);
        string toString();
        bool equals(Cubicle& cub);
        int getAdjNum();
        void increaseAdjNum();
        int getIterator();
        void increaseIterator();
        void checkIterator();
};
#endif