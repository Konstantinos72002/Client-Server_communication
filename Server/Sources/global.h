#include "headers.h"

#ifndef GLOBAL_H
#define GLOBAL_H
extern pthread_t master_thread;
extern pthread_t *worker_threads;
extern int size_of_worker_threads;
extern bool flag;
extern list<int> buffer;
extern set<string> voters;
extern map<string,int> votes;
extern pthread_mutex_t buffer_mtx ;
extern pthread_cond_t cvar_noempty;
extern pthread_cond_t cvar_nofull;
extern pthread_mutex_t voters_mtx;
extern pthread_mutex_t votes_mtx;
extern pthread_mutex_t file_mtx;
extern pthread_mutex_t main_mtx;
extern string file;
#endif // GLOBAL_H