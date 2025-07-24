#ifndef REACTOR_HPP
#define REACTOR_HPP

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*reactorFunc)(int fd);

struct reactor;

void* startReactor();

int addFdToReactor(void* reactor, int fd, reactorFunc func);

int removeFdFromReactor(void* reactor, int fd);

int stopReactor(void* reactor);

int runReactor(void* reactor);

#ifdef __cplusplus
}
#endif
