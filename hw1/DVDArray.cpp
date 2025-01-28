#include <iostream>
using namespace std;
#include "DVDArray.h"

DVDArray::DVDArray(const int aSize = 0){
    if(aSize <= 0){
        size = 0;
        data = nullptr;
    }
    else{
        size = aSize;
        data = new DVD[size];
    }
}

DVDArray::~DVDArray(){
    if(data){
        delete[] data;
    }
}

int DVDArray::getSize()const{
    return size;
}

DVD& DVDArray::operator[](int ind)const{
    if(ind < 0 || ind >= size){
        throw out_of_range("Invalid index");
    }
    else{
        return data[ind];
    }
}

int DVDArray::findDVD(const string serialNo) const{
    if(size > 0){
        for(int i = 0; i < size; i++){
            if(data[i].getSerialNo() == serialNo){
                return i;
            }
        }
    }
    return -1;
}
int DVDArray::addDVD(DVD dvd) {
    if(findDVD(dvd.getSerialNo()) == -1){
        if(size == 0){
            data = new DVD[size+1];
            data[size] = dvd;
        }
        else{
            DVD* temp = data;
            data = new DVD[size+1];
            for(int i = 0; i < size; i++){
                data[i] = temp[i];
            }
            data[size] = dvd;
            delete[] temp;
        }
        size++;
        return 0;
    }
    return -1;
} 
void DVDArray::removeDVD(const int removedIndex){
    if(size > 1){
        DVD* temp = data;
        data = new DVD[size-1];
        int index = 0;
        for(int j = 0; j < size; j++){
            if(j != removedIndex){
                data[index++] = temp[j];
            }
        }
        delete[] temp;
    }  
    else{
        data = nullptr;
    } 
    size--;
} 

