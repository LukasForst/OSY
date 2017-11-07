//
// Created by lukas on 11/7/17.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "workplace_chain.h"
#include "job_handler.h"

job_type get_job_type(char type) {
    switch (type) {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        default:
            break;
    }
    //todo better error handling
    return (job_type) -1; //not defined
}


_Bool command_make() {
    char char_type;
    if (scanf(" %c", &char_type) != 1) {
        //todo error handling
        return false;
    }

    job_type type = get_job_type(char_type);
    job_t *job = (job_t *) malloc(sizeof(job_t));
    job->type = type;
    job->current_workplace = NOT_STARTED;

    workplace_type place = get_next_work_place(job);
    int sleep_time = get_sleep_time(place);

    job->current_workplace = place;
    job->sleep_time = sleep_time;
    add_job(job);
    return true;
}


_Bool command_start() {
    return true;
}

_Bool command_end() {

    return true;
}

_Bool command_add() {

    return true;
}

_Bool command_remove() {

    return true;
}