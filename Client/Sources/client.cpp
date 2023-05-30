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
        istringstream iss(line);
        iss >> v->name;
        iss >> v->surname;
        iss >> v->party;
        votes.push_back(v);

        pthread_t thread;
        
        total_arguments targs = new Total_Arguments;
        targs->clientArgsptr= args;
        targs->voteptr = v;
        targs_vector.push_back(targs);

        pthread_create(&thread, nullptr, thread_func, targs);
        threads.push_back(thread);
    }
    
    for (pthread_t& thread : threads) {
        if (pthread_join(thread, nullptr) != 0) {
            std::cerr << "Failed to join a thread." << std::endl;
        }
    }
    
    for (auto vote : votes) {
        delete vote;
    }
    
    for (auto t : targs_vector) {
        delete t;
    }

    delete(args);
    
    return 0;
}
