#ifndef CUBICLESTACK_H
#define CUBICLESTACK_H
#include <string>
#include <iostream>
#include "Cubicle.h"
class CubicleStack
{
private:
    static const int capasity = 100000;
    Cubicle* stack[capasity];
    int top;
public:
    CubicleStack();
    bool isEmpty() const;
    bool push(Cubicle* cub);
    bool pop();
    Cubicle& peek();
    void printStack();
    
};
#endif

