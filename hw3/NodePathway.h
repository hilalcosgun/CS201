//Hilal Coşgun 22201571 Section:2
#ifndef NODEPATHWAY__
#define NODEPATHWAY__
#include "NodeProtein.h"
#include <string>
using namespace std;
class NodePathway{
private:
    int ID;
    string name;
    NodeProtein* proteinListHeader;
    NodePathway* next;
    int proteinCount;
    
public:
NodePathway(const int ID = 0, const string name="");
~NodePathway();
int getID() const; 
string getName() const;
int getProteinCount() const;
NodeProtein* getProteinListHeader() const;
int getTotalGenCount() const;
NodePathway* getNext() const;
void setID(const int ID);
void setName(const string name);
void setNext(NodePathway*);
void addProtein(const int proteinId) ;
void removeProtein(const int proteinId);
NodeProtein* findProtein(const int proteinID) const;
void removeFirstProtein();
};

#endif