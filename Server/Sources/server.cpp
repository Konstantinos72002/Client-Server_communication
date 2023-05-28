#include "headers.h"

int main(int argc, char* argv[]) {    
    
    if (argc != 6) {
        cerr << "Wrong arguments" << endl;
        exit(1);
    }
    string a(argv[4]);
    string b(argv[5]);
    server_arguments args = new Server_Arguments;
    args->portnum = atoi(argv[1]);
    args->numWorkerthreads = atoi(argv[2]);
    args->bufferSize = atoi(argv[3]);
    args->poll_log = a;
    args->poll_stats = b;

    pthread_t master_thread;

    pthread_create(&master_thread, NULL,&master,(void*)args);
    
    pthread_join(master_thread,NULL);

    delete args;
    return 0;
}
