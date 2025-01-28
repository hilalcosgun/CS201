
#include <string>
#include <iostream>
#include "CubicleStack.h"
CubicleStack::CubicleStack(){
    top = -1;
}

bool CubicleStack::isEmpty() const{
    return top < 0;
}
bool CubicleStack::push(Cubicle* cub){
    if(top < capasity -1){
        top++;
        stack[top] = cub;
        return true;
    }
    return false;
}
bool CubicleStack::pop(){
    if(!isEmpty()){
        top--;
        return true;
    }
    return false;
}
Cubicle& CubicleStack::peek(){
    return *(stack[top]);
}
void CubicleStack::printStack(){
    
    for (int i = 0; i < top+1; i++){
        cout<<(*stack[i]).toString();
        if(i < top){
            cout<<" -> ";
        }
    }
    cout<<endl;
}

