//Hilal Coşgun 22201571 Section:2
#ifndef NODEPROTEIN__
#define NODEPROTEIN__
#include "NodeGen.h"
class NodeProtein{
private:
    int ID;
    NodeGen* genListHeader;
    NodeProtein* next;
    int genCount; 
public:
    NodeProtein(const int ID = 0);
    ~NodeProtein();
    int getID() const;
    int getGenCount() const;
    NodeGen* getGenListHeader() const;
    NodeProtein* getNext() const;
    void setID(const int ID);
    void setNext(NodeProtein* nextNode);
    void addGen(const int genId,const string genName);
    void removeGen(const int geneID);
    string printGenes()const;
    NodeGen* findGen(const int genID) const;
    void removeFirstGene();
};
#endif