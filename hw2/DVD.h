//Hilal Coşgun 
//Sec2
//22201571
#ifndef _DVD_H
#define _DVD_H
#include <string>
using namespace std; 
class DVD{
private:
    string serialNo;
    string title;
    string director;
    bool isAvailable;
public:
    DVD();
    DVD(const string serialNo,const string title,const string director);
    string toString() const;
    string getSerialNo() const;
    string getTitle() const;
    string getDirector()const;
    bool getAvailability()const;
    void setAvailability(const bool availability);
};
#endif

