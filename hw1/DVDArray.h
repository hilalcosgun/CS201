#include <string>
#include "DVD.h"
using namespace std;
class DVDArray{
private:
    DVD* data;
    int size;
public:
    DVDArray(const int = 0);
    ~DVDArray();
    DVD& operator[](int ind) const;
    int getSize() const;
    int findDVD(string serialNo) const;
    int addDVD(const DVD dvd);
    void removeDVD(const int removedIndex);
};


