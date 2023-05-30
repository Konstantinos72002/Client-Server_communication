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

int insert_to_buffer(int,int);

int get_from_buffer();

bool insert_to_set(char*);

void signalHandler(int);

bool insert_to_map(char*);

void create_stats_file(string);