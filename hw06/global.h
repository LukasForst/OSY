//
// Created by lukas on 11/7/17.
//

#ifndef HW06_GLOBAL_H
#define HW06_GLOBAL_H

#include <pthread.h>
#include <semaphore.h>

typedef enum {
    NOT_STARTED, SCISSORS, DRILL, BENDING_MACHINE, WELDER, PAINTER, SCREWDRIVER, MILLING_CUTTER, FINISHED
} workplace_type;

typedef enum {
    A, B, C
} job_type;


typedef struct workplace {
    _Bool is_working; //determines whether is mutex locked and whether is this workspace active or not

    workplace_type type;
    pthread_mutex_t mutex;
    sem_t added; //signal, that job has been added

    struct workplace *next_workplace; // for linked list
} workplace_t;


typedef struct {
    char *name; //name of worker
    volatile _Bool is_working; //determines whether is worker working right now
    volatile _Bool is_active; //determines whether is worker going to be disposed or not
    workplace_t *workplace; //workplace where is this particular worker
    sem_t wakeup; //wakes up worker
} worker_info_t;

typedef struct job {
    __useconds_t sleep_time;
    int step;
    job_type type;
    workplace_type previous_workplace;
    workplace_type current_workplace;

    struct job *next_job; // for linked list
} job_t;

#endif //HW06_GLOBAL_H