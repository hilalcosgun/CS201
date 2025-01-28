//Hilal Coşgun 22201571 Section:2
#include "NodePathway.h"
#include <string>
using namespace std;

class BiologicalPathway {
private:
    NodePathway* pathwayListHeader;
    int pathwayCount;

public:
    BiologicalPathway();
    ~BiologicalPathway();
    void addPathway( const int pathwayId, const string pathwayName );
    void removePathway( const int pathwayId );
    void printPathways() const;

    void addProtein( const int proteinId, const int pathwayId );
    void removeProtein( const int proteinId, const int pathwayId );
    void printProteinsInPathway( const int pathwayId ) const;

    void addGene( const int geneID, const string geneName, const int proteinId );
    void removeGene( const int geneID, const int proteinId );
    void printGenesOfProtein( const int proteinId ) const;

    NodePathway* findPathway(const int pathwayID) const;
    void removeFirstPathway();

 };
