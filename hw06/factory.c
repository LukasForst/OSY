//
// Created by lukas on 11/7/17.
//
#include <stdlib.h>
#include "factory.h"
#include "buffers.h"

void add_job(workplace_name name, job_t *work_to_add) {
    switch (name) {
        case SCISSORS:
            add_scissors_job(work_to_add);
        case DRILL:
            add_drill_job(work_to_add);
        case BENDING_MACHINE:
            add_bending_machine_job(work_to_add);
        case WELDER:
            add_welder_job(work_to_add);
        case PAINTER:
            add_painter_job(work_to_add);
        case SCREWDRIVER:
            add_srewdriver_job(work_to_add);
        case MILLING_CUTTER:
            add_milling_job(work_to_add);
        case FINISHED:
            return;
    }
}

job_t *get_job(workplace_name name) {
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
        case FINISHED:
            return NULL;
    }
    return NULL;
}