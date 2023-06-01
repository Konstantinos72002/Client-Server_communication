#include "headers.h"

list<int> buffer;
set<string> voters;
map<string,int> votes;
string file;

bool flag = false;
pthread_mutex_t buffer_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvar_noempty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cvar_nofull = PTHREAD_COND_INITIALIZER;

pthread_mutex_t voters_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t votes_mtx = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t file_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t main_mtx = PTHREAD_MUTEX_INITIALIZER;

pthread_t master_thread;
pthread_t *worker_threads;
int size_of_worker_threads;


int insert_to_buffer(int clientsock,int bufferSize) {
    pthread_mutex_lock(&buffer_mtx);
    int current_buffer_size = buffer.size();
    while (current_buffer_size == bufferSize) {
        pthread_cond_wait(&cvar_nofull, &buffer_mtx);
        if (flag) {
            pthread_mutex_unlock(&buffer_mtx);
            return -1;
        }
    }
    buffer.push_back(clientsock);
    // cout << "insert " << clientsock << " " << buffer.size() << endl;
    pthread_cond_broadcast(&cvar_noempty);
    
    pthread_mutex_unlock(&buffer_mtx);
    return 0;
}

int get_from_buffer() {
    
    pthread_mutex_lock(&buffer_mtx);
    
    int clientsock;
    while (buffer.size() <= 0) {
    
        pthread_cond_wait(&cvar_noempty, &buffer_mtx);
    
        if (flag) {
            pthread_mutex_unlock(&buffer_mtx);
            return -1;
        }
    }
    clientsock = buffer.front();
    buffer.pop_front();
    // cout << "get" << buffer.size() << endl;
    pthread_cond_broadcast(&cvar_nofull);
    
    pthread_mutex_unlock(&buffer_mtx);
    return clientsock;
}

bool insert_to_set(char* name) {

    pthread_mutex_lock(&voters_mtx);

    if (voters.find(name) != voters.end()) {
    
        pthread_mutex_unlock(&voters_mtx);
    
        return true;
    }
    voters.insert(name);
    
    pthread_cond_signal(&cvar_noempty);
    pthread_mutex_unlock(&voters_mtx);
    return false;
}

bool insert_to_map(char* name) {
   
    pthread_mutex_lock(&votes_mtx);
   
    if (votes.find(name) != votes.end()) {
        votes[name]++;
        pthread_mutex_unlock(&votes_mtx);
        return true;
    }
    votes[name] = 1;
    pthread_mutex_unlock(&votes_mtx);
    return false;
}

void signalHandler(int signum) {

    flag = true;

    pthread_mutex_unlock(&buffer_mtx);
    
    pthread_cond_broadcast(&cvar_noempty);
    pthread_cond_broadcast(&cvar_nofull);

    for (int i = 0; i < size_of_worker_threads; i++) {
        pthread_join(worker_threads[i], NULL);
    }
    
    create_stats_file(file);

    pthread_detach(master_thread);

    pthread_mutex_destroy(&buffer_mtx);
    pthread_cond_destroy(&cvar_noempty);
    pthread_cond_destroy(&cvar_nofull);
    pthread_mutex_destroy(&voters_mtx);
    pthread_mutex_destroy(&votes_mtx);
    pthread_mutex_destroy(&file_mtx);

    buffer.clear();
    voters.clear();
    votes.clear();

    delete[] worker_threads;
    
    // pthread_mutex_unlock(&main_mtx);
    cout << "done" << endl;
    return;
}

void create_stats_file(string poll_stats) {
    
    ofstream stats_file;
    stats_file.open(poll_stats.c_str(),ios::app);
    int total_votes = 0;
    
    for (map<string,int>::iterator it = votes.begin(); it != votes.end(); it++) {
        stats_file << it->first << " " << it->second << endl;
        total_votes += it->second;
    }
    stats_file << "Total " << total_votes << endl;
    stats_file.close();
    return;
}