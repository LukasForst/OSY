//
// Created by lukas on 11/7/17.
//

#ifndef HW06_GLOBAL_H
#define HW06_GLOBAL_H

typedef enum {
    SCISSORS, DRILL, BENDING_MACHINE, WELDER, PAINTER, SCREWDRIVER, MILLING_CUTTER, FINISHED
} workplace_name;

typedef enum{
    A,B,C
} job_type;

typedef struct {
    int worker_number;
    _Bool is_active;
    char *name;
} worker_t;

typedef struct {
    workplace_name name;
    worker_t **workers;
} work_place;

typedef struct work {
    int sleep_time;
    job_type type;
    workplace_name current_place;

    struct work *next_work; // for linked list
} job_t;




#endif //HW06_GLOBAL_H
