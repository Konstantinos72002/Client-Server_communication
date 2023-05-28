#include "headers.h"

extern list<int> buffer;
extern set<string> voters;
extern pthread_mutex_t buffer_mtx ;
extern pthread_cond_t cvar_buffer;

extern pthread_mutex_t voters_mtx ;