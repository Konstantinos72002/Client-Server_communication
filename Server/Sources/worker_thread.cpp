#include "headers.h"

void* worker(void* file) {
    
    string *file_name_s = (string*)file;
    string file_name_s2 = *file_name_s;
    char* file_name = new char[file_name_s2.length() + 1];
    strcpy(file_name, file_name_s2.c_str());

    int clientsock = get_from_buffer();
    cout << "Worker thread " << pthread_self() << " got connection from client with socket " << clientsock << endl;
    
    if(write(clientsock,"SEND VOTE PLEASE",sizeof("SEND VOTE PLEASE")) == -1) {
        perror("write");
        exit(1);
    }
    
    char name[256];
    char party[256];
    if(read(clientsock,name,sizeof(name)) == -1) {
        perror("file read\n");
        exit(1);
    }

    if(insert_to_set(name)) {
        if(write(clientsock,"ALREADY VOTED",sizeof("ALREADY VOTED")) == -1) {
            perror("write");
            exit(1);
        }

        close(clientsock);
        return NULL;
    } else {

        if(write(clientsock,"SEND VOTE PLEASE",sizeof("SEND VOTE PLEASE")) == -1) {
            perror("write");
            exit(1);
        }
        if(read(clientsock,party,sizeof(party)) == -1) {
            perror("file read\n");
            exit(1);
        }

        FILE *file = fopen(file_name, "a");
        if (file == NULL) {
            perror("fopen");
            exit(1);
        }
        
        fprintf(file,"%s %s\n",name, party);
        fclose(file);

        int totalLength = strlen("VOTE for") + strlen(party) + strlen("RECORDED") + 1;
        char* message = new char[totalLength];
        strcat(message,"VOTE for");
        strcat(message,party);
        strcat(message,"RECORDED");

        if(write(clientsock,message,sizeof(message)) == -1) {
            perror("write");
            exit(1);
        }
        
        close(clientsock);
        return NULL;
    }


        

    return NULL;
}