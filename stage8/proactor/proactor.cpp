#include "proactor.hpp"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct ThreadArgs {
    int sockfd;
    proactorFunc func;
};

static void* threadEntry(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    void* result = args->func(args->sockfd);
    close(args->sockfd);
    free(args);
    return result;
}

pthread_t startProactor(int sockfd, proactorFunc func) {
    pthread_t tid;
    ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
    args->sockfd = sockfd;
    args->func = func;
    pthread_create(&tid, NULL, threadEntry, args);
    return tid;
}

int stopProactor(pthread_t tid) {
    return pthread_cancel(tid);
}
