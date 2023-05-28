#include "headers.h"

// void insert_to_buffer(int clientsock,int bufferSize) {
//     int current_buffer_size = buffer.size();
//     pthread_mutex_lock(&buffer_mtx);
//     while (current_buffer_size == bufferSize) {
//         pthread_cond_wait(&cvar_buffer, &buffer_mtx);
//     }
//     buffer.push_back(clientsock);
//     pthread_cond_signal(&cvar_buffer);
//     pthread_mutex_unlock(&buffer_mtx);
// }
 
// int get_from_buffer() {
//     int clientsock;
//     pthread_mutex_lock(&buffer_mtx);
//     while (buffer.size() == 0) {
//         pthread_cond_wait(&cvar_buffer, &buffer_mtx);
//     }
//     clientsock = buffer.front();
//     buffer.pop_front();
//     pthread_cond_signal(&cvar_buffer);
//     pthread_mutex_unlock(&buffer_mtx);
//     return clientsock;
// }

// bool insert_to_set(char* name) {
//     pthread_mutex_lock(&voters_mtx);
//     if (voters.find(name) != voters.end()) {
//         pthread_mutex_unlock(&voters_mtx);
//         return true;
//     }
//     voters.insert(name);
//     pthread_mutex_unlock(&voters_mtx);
//     return false;
// }