#include "headers.h"

void child_server(int newsock);

void* master(void* args) {
    server_arguments arg = (server_arguments)args;
    int portnum = arg->portnum;
    int numWorkerthreads = arg->numWorkerthreads;
    int bufferSize = arg->bufferSize;
    string poll_log = arg->poll_log;
    string poll_stats = arg->poll_stats;
    
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
    
    server.sin_family = AF_INET; /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    cout << server.sin_addr.s_addr << endl;
    server.sin_port = htons(portnum); /* The given port */
   
    if (bind(mastersock, serverptr, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(mastersock, bufferSize) < 0) { 
        perror("listen");
        exit(1);
    }
    printf("Listening for connections to port %d\n", portnum);
    
    while (1) { 
        cout << "here" << endl;
        clientlen = sizeof(client);
        
        if ((clientsock = accept(mastersock, clientptr, &clientlen)) < 0) {
            perror("accept");
            exit(1);
        }
        
        if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), client.sin_family)) == NULL) {
            perror("gethostbyaddr"); 
            exit(1);
        }

        printf("Accepted connection from %s\n", rem->h_name);
        switch (fork()) { /* Create child for serving client */
            case -1: /* Error */
                perror("fork"); break;
            case 0: /* Child process */
                close(mastersock); child_server(clientsock);
            exit(0);
            default: /* Parent process */
                wait(NULL);
                close(clientsock);
        }
            // close(clientsock); /* parent closes socket to client */
    }
}

void child_server(int newsock) {
    cout << "newsock: " << newsock << endl;
    return;
}
    