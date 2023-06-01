#include "headers.h"

void* thread_func(void* arguments) {

    total_arguments args = (total_arguments)arguments;
    vote v = args->voteptr;
    string voterName = v->name + " " + v->surname;
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
    
    // cout << " daino " << sock << endl;
    
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

    char a[256];
    if(read(sock,a,sizeof(a)) == -1) {
        perror("file read\n");
        exit(1);
    }

    // send name please
    // cout << "pthread id: " << " " << pthread_self() << " " << a << endl;

    int len = voterName.length() + 1;
    
    if(write(sock,voterName.c_str(),len) == -1) {
        perror("write");
        exit(1);
    }

    // already voted || send vote please
    char b[256];
    if(read(sock,b,sizeof(b)) == -1) {
        perror("file read\n");
        exit(1);
    }

    // cout << "pthread id: " << " " << pthread_self() << " " << b << endl;

    if(strcmp(b,"SEND VOTE PLEASE") == 0) {
        int len = v->party.length() + 1;
        if(write(sock,v->party.c_str(),len) == -1) {
            perror("write");
            exit(1);
        }
    }

    char c[256];
    if (read(sock,c,sizeof(c)) < 0) {
        perror("read");
        exit(1);
    }

    pthread_exit(NULL);
    return NULL;
}