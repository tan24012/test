#include "MThread.h"

void *threadEntry(void *mt) {
    MThread *mt_local = (MThread *)mt;
    mt_local->run(mt_local->arg);

    return NULL;
}

void mtInit(MThread *mt) {
    if(!mt) return;

    mt->run = NULL;
    mt->arg = NULL;
    mt->started = false;
    mt->joined = false;
}

int mtStart(MThread *mt) {
    if(mt->started || !mt->run || !mt->arg) return -1;

    int ret = pthread_create(&mt->thread_ID, NULL, threadEntry, (void *)mt);
    if(!ret) mt->started = true;
    
    return ret;
}

int mtWait(MThread *mt) {
    if(!mt->started || mt->joined) return -1;

    int ret = pthread_join(mt->thread_ID, NULL);
    if(!ret) mt->joined = true;

    return ret;
}