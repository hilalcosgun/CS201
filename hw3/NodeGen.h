//Hilal Coşgun 22201571 Section:2
#ifndef NODEGEN__
#define NODEGEN__
#include <string>
using namespace std;
class NodeGen{
private:
    int ID;
    string name;
    NodeGen* next;
public:
    NodeGen(const int ID = 0, const string name ="");
    ~NodeGen();
    int getID() const; 
    string getName() const;
    NodeGen* getNext() const;
    void setID(const int ID);
    void setNext(NodeGen* next);
};

#endif
