#include "headers.h"

void* worker(void* file) {
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    string *file_name_s = (string*)file;
    string file_name_s2 = *file_name_s;
    char file_name[256];
    strcpy(file_name, file_name_s2.c_str());

    while(1) {

        int clientsock = get_from_buffer();
        if(clientsock == -1) {
            return NULL;
        }
        
        if(write(clientsock,"SEND NAME PLEASE",sizeof("SEND NAME PLEASE")) == -1) {
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
            
        } else {

            if(write(clientsock,"SEND VOTE PLEASE",sizeof("SEND VOTE PLEASE")) == -1) {
                perror("write");
                exit(1);
            }

            if(read(clientsock,party,sizeof(party)) == -1) {
                perror("file read\n");
                exit(1);
            }
            
            insert_to_map(party);

            FILE *fp = fopen(file_name, "a");
            if (file == NULL) {
                perror("fopen");
                exit(1);
            }


            pthread_mutex_lock(&file_mtx);

            fprintf(fp,"%s %s\n",name, party);
            fclose(fp);

            pthread_mutex_unlock(&file_mtx);
            
            int totalLength = strlen("VOTE for") + strlen(party) + strlen("RECORDED") + 1;
            char message[totalLength];
            strcat(message,"VOTE for ");
            strcat(message,party);
            strcat(message," RECORDED");

            if(write(clientsock,message,totalLength) == -1) {
                perror("write");
                exit(1);
            }
        }
        close(clientsock);
        
    }     
    return NULL;
}