//
// Created by lukas on 11/7/17.
//
#include "job_handler.h"
#include "buffers.h"

void add_job(job_t *job_to_add) {
    //todo notify all workers
    switch (job_to_add->current_workplace) {
        case SCISSORS:
            add_scissors_job(job_to_add);
            break;
        case DRILL:
            add_drill_job(job_to_add);
            break;
        case BENDING_MACHINE:
            add_bending_machine_job(job_to_add);
            break;
        case WELDER:
            add_welder_job(job_to_add);
            break;
        case PAINTER:
            add_painter_job(job_to_add);
            break;
        case SCREWDRIVER:
            add_srewdriver_job(job_to_add);
            break;
        case MILLING_CUTTER:
            add_milling_job(job_to_add);
            break;
        default:
            break;
    }
}

job_t *get_job(workplace_type name) {
    switch (name) {
        case SCISSORS:
            return get_scissors_job();
        case DRILL:
            return get_drill_job();
        case BENDING_MACHINE:
            return get_bending_machine_job();
        case WELDER:
            return get_welder_job();
        case PAINTER:
            return get_painter_job();
        case SCREWDRIVER:
            return get_screwdriver_job();
        case MILLING_CUTTER:
            return get_milling_job();
        default:
            return NULL;
    }
    return NULL;
}