#include "reactor.hpp"
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define MAX_FDS 1024

struct reactor {
    fd_set master_fds;          
    fd_set read_fds;            
    int max_fd;
    reactorFunc funcs[MAX_FDS];
    int running;
};

void* startReactor() {
    struct reactor* r = (struct reactor*)malloc(sizeof(struct reactor));
    if (!r) {
        return NULL;
    }

    FD_ZERO(&r->master_fds);
    FD_ZERO(&r->read_fds);
    r->max_fd = -1;
    r->running = 0;

    for (int i = 0; i < MAX_FDS; i++) {
        r->funcs[i] = NULL;
    }
    
    return (void*)r;
}

int addFdToReactor(void* reactor_ptr, int fd, reactorFunc func) {
    if (!reactor_ptr || fd < 0 || fd >= MAX_FDS || !func) {
        return -1;
    }
    
    struct reactor* r = (struct reactor*)reactor_ptr;

    FD_SET(fd, &r->master_fds);

    if (fd > r->max_fd) {
        r->max_fd = fd;
    }

    r->funcs[fd] = func;
    
    return 0;
}

int removeFdFromReactor(void* reactor_ptr, int fd) {
    if (!reactor_ptr || fd < 0 || fd >= MAX_FDS) {
        return -1;
    }
    
    struct reactor* r = (struct reactor*)reactor_ptr;

    FD_CLR(fd, &r->master_fds);

    r->funcs[fd] = NULL;

    if (fd == r->max_fd) {
        r->max_fd = -1;
        for (int i = MAX_FDS - 1; i >= 0; i--) {
            if (FD_ISSET(i, &r->master_fds)) {
                r->max_fd = i;
                break;
            }
        }
    }
    
    return 0;
}

int runReactor(void* reactor_ptr) {
    if (!reactor_ptr) {
        return -1;
    }
    
    struct reactor* r = (struct reactor*)reactor_ptr;
    r->running = 1;
    
    while (r->running) {
        r->read_fds = r->master_fds;

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int activity = select(r->max_fd + 1, &r->read_fds, NULL, NULL, &tv);
        
        if (activity < 0) {
            if (errno != EINTR) {
                perror("select error");
                return -1;
            }
            continue; 
        }
        
        if (activity == 0) {
            continue;
        }

        for (int fd = 0; fd <= r->max_fd; fd++) {
            if (FD_ISSET(fd, &r->read_fds)) {
                if (r->funcs[fd]) {
                    r->funcs[fd](fd);
                }
            }
        }
    }
    
    return 0;
}

int stopReactor(void* reactor_ptr) {
    if (!reactor_ptr) {
        return -1;
    }
    
    struct reactor* r = (struct reactor*)reactor_ptr;
    r->running = 0;
    
    FD_ZERO(&r->master_fds);
    FD_ZERO(&r->read_fds);
    
    for (int i = 0; i < MAX_FDS; i++) {
        r->funcs[i] = NULL;
    }
    
    free(r);
    
    return 0;
}
