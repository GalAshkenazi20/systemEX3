#ifndef PROACTOR_HPP
#define PROACTOR_HPP

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*proactorFunc)(int sockfd);

pthread_t startProactor(int sockfd, proactorFunc func);
int stopProactor(pthread_t tid);

#ifdef __cplusplus
}
#endif

#endif
