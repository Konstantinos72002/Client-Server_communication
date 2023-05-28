#include "headers.h"
using namespace std;

struct Client_Arguments
{
    string serverName;
    int portNum;
    string inputFile;
} typedef *client_arguments;

struct Vote {
        string name;
        string surname;
        string party;
} typedef *vote;

struct Total_Arguments {
    client_arguments clientArgsptr;
    vote             voteptr;
} typedef *total_arguments;

void *thread_func(void*);