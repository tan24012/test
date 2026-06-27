#ifndef MTHREAD_H
#define MTHREAD_H

#include <pthread.h>
#include <stdbool.h>

typedef struct {
    pthread_t thread_ID;
    void (*run)(void *);
    void *arg;
    bool started;
    bool joined;
} MThread;

void mtInit(MThread *mt);
int mtStart(MThread *mt);
int mtWait(MThread *mt);

#endif