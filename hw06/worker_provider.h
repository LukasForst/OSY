//
// Created by lukas on 11/7/17.
//

#ifndef HW06_WORKER_PROVIDER_H
#define HW06_WORKER_PROVIDER_H

#include <pthread.h>
#include "global.h"

pthread_t create_worker(char *name, workplace_t *workplace);

void remove_worker(char *name);

void free_workers();

#endif //HW06_WORKER_PROVIDER_H
