#include <string>
using namespace std;
class Transaction
{
private:
    string transaction;
    int customerID;
    string serialNo; 
    
public:
    Transaction();
    Transaction(const string transaction,const int customerID, const string serialNo );
    string toString();
};
