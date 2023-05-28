#include "headers.h"

struct Server_Arguments
{
    int portnum;
    int numWorkerthreads;
    int bufferSize;
    string poll_log;
    string poll_stats;
} typedef *server_arguments;

void *master(void*);

void* worker(void*);

void insert_to_buffer(int,int);

int get_from_buffer();

// true if have aleready vote
bool insert_to_set(char*);