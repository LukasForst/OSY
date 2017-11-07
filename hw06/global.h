//
// Created by lukas on 11/7/17.
//

#ifndef HW06_GLOBAL_H
#define HW06_GLOBAL_H

#include <pthread.h>

typedef enum {
    NOT_STARTED, SCISSORS, DRILL, BENDING_MACHINE, WELDER, PAINTER, SCREWDRIVER, MILLING_CUTTER, FINISHED
} workplace_type;

typedef enum {
    A, B, C
} job_type;


typedef struct workplace {
    _Bool is_working; //determines whether is mutex locked and whether is this workspace active or not
    _Bool is_active; //when set to false, workplace will be disposed

    workplace_type type;
    pthread_mutex_t mutex;

    struct workplace *next_workplace; // for linked list
} workplace_t;


typedef struct {
    int worker_number; //id of worker
    _Bool is_active; //determines whether is worker working right now
    char *name; //name of worker
    workplace_t *workplace; //workplace where is this particular worker
} worker_t;

typedef struct job {
    int sleep_time;
    int step;
    job_type type;
    workplace_type current_workplace;

    struct job *next_job; // for linked list
} job_t;

#endif //HW06_GLOBAL_H