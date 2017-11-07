//
// Created by lukas on 11/7/17.
//

#ifndef HW06_GLOBAL_H
#define HW06_GLOBAL_H

#include <pthread.h>

typedef enum {
    NOT_STARTED, SCISSORS, DRILL, BENDING_MACHINE, WELDER, PAINTER, SCREWDRIVER, MILLING_CUTTER, FINISHED
} workplace_type;

typedef enum{
    A,B,C
} job_type;


typedef struct {
    workplace_type type;
    pthread_mutex_t mutex;
} workplace_t;


typedef struct {
    int worker_number;
    _Bool is_active;
    char *name;
    workplace_t workplace;
} worker_t;

typedef struct job {
    int sleep_time;
    job_type type;
    workplace_type current_workplace;

    struct job *next_job; // for linked list
} job_t;

#endif //HW06_GLOBAL_H