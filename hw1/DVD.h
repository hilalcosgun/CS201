#include <string>
using namespace std; 
class DVD{
private:
    string serialNo;
    string title;
    string director;
    string isAvailable;
public:
    DVD();
    DVD(const string serialNo,const string title,const string director);
    string toString();
    string getSerialNo();
    string getTitle();
    string getDirector();
    string getAvailability();
    void setAvailability(const string availability);
};





//DVD: 001, Title: Inception, Director: Christopher Nolan, Available