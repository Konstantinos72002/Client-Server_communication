#include "headers.h"

void perror_exit(string message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}