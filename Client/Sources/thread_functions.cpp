#include "headers.h"

void* thread_func(void* arguments) {

    total_arguments args = (total_arguments)arguments;
    vote v = args->voteptr;
    client_arguments cargs = args->clientArgsptr;
    int portnum = cargs->portNum;
    string serverName = cargs->serverName;
    string inputFile = cargs->inputFile;
    int sock;
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct hostent *rem;
 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    
    if ((rem = gethostbyname(serverName.c_str())) == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    server.sin_family = AF_INET;
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(portnum);
    if (connect(sock, serverptr, sizeof(server)) < 0) {
        perror("connect");
        exit(1);
    }
    // char* buffer = new char[1024];
    // if (write(sock, buffer, 1024) < 0) {
    //     perror("write");
    //     exit(1);
    // }

    // delete[] buffer;
    close(sock);
    return NULL;
}