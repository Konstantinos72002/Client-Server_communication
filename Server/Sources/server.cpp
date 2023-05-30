#include "headers.h"

int main(int argc, char* argv[]) {    
    
    if (argc != 6) {
        cerr << "Wrong arguments" << endl;
        exit(1);
    }

    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    string a(argv[4]);
    string b(argv[5]);
    server_arguments args = new Server_Arguments;
    args->portnum = atoi(argv[1]);
    args->numWorkerthreads = atoi(argv[2]);
    size_of_worker_threads = args->numWorkerthreads;
    args->bufferSize = atoi(argv[3]);
    args->poll_log = a;
    args->poll_stats = b;

    pthread_create(&master_thread, NULL,&master,(void*)args);
    pthread_join(master_thread,NULL);

    delete args;

    return 0;
}
