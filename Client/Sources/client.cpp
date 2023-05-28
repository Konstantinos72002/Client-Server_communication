#include "headers.h"

int main(int argc, char* argv[]) {    
    
    if (argc != 4) {
        cerr << "Wrong arguments" << endl;
        exit(1);
    }
    string a(argv[1]);
    string b(argv[3]);
    client_arguments args = new Client_Arguments;
    args->serverName = a;
    args->portNum = atoi(argv[2]);
    args->inputFile = b;

    ifstream file(args->inputFile);
    string line;
    vector<pthread_t> threads;
    vector<vote> votes;
    vector<total_arguments> targs_vector;
    while(getline(file, line)) {
        vote v = new Vote;
        votes.push_back(v);

        istringstream iss(line);
        iss >> v->name;
        iss >> v->surname;
        iss >> v->party;
        
        pthread_t thread;
        threads.push_back(thread);

        total_arguments targs = new Total_Arguments;
        targs_vector.push_back(targs);
        targs->clientArgsptr= args;
        targs->voteptr = v;
        pthread_create(&thread, NULL, thread_func, (void*)targs);
        pthread_join(thread,NULL);
    }

    for (auto t : threads) {
        pthread_join(t,NULL);
    }
    delete args;
    for (auto vote : votes) {
        delete vote;
    }
    for (auto t : targs_vector) {
        delete t;
    }
    
    return 0;
}
