#include "headers.h"

void* master(void* args) {

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);

    server_arguments arg = (server_arguments)args;
    int portnum = arg->portnum;
    int numWorkerthreads = arg->numWorkerthreads;
    int bufferSize = arg->bufferSize;
    string poll_log = arg->poll_log;
    string poll_stats = arg->poll_stats;
    file = poll_stats;

    FILE *flog;
    flog = fopen(poll_log.c_str(), "w");
    fclose(flog);
    FILE *fstats;
    fstats = fopen(poll_stats.c_str(), "w");
    fclose(fstats);

    worker_threads = new pthread_t[numWorkerthreads];

    for(int i=0;i<numWorkerthreads;i++) {
        pthread_create(&worker_threads[i], NULL,&worker,(void*)&poll_log);
    }

    int mastersock,clientsock;

    struct sockaddr_in server, client;
    socklen_t clientlen;
    struct sockaddr *serverptr=(struct sockaddr *)&server;
    struct sockaddr *clientptr=(struct sockaddr *)&client;
    struct hostent *rem;
    
    if ((mastersock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(portnum);
   
    if (bind(mastersock, serverptr, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(mastersock, 10000) < 0) { 
        perror("listen");
        exit(1);
    }
    
    printf("Listening for connections to port %d\n", portnum);
    
    while (1) {
        
        clientlen = sizeof(client);
        
        if ((clientsock = accept(mastersock, clientptr, &clientlen)) < 0) {
            cout << endl << "End connection" << endl;
            return NULL;
        }

        if(insert_to_buffer(clientsock,bufferSize) == -1) {
            return NULL;
        }

    }

    return NULL;
}