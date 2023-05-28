#include "headers.h"
using namespace std;
struct Server_Arguments
{
    int portnum;
    int numWorkerthreads;
    int bufferSize;
    string poll_log;
    string poll_stats;
} typedef *server_arguments;

void *master(void*);