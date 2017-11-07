//
// Created by lukas on 11/7/17.
//

#ifndef HW06_BUFFERS_H
#define HW06_BUFFERS_H

#include "global.h"

void buffers_init();

job_t * get_scissors_job();
void add_scissors_job(job_t* work_to_add);

job_t * get_drill_job();
void add_drill_job(job_t* work_to_add);

job_t * get_bending_machine_job();
void add_bending_machine_job(job_t* work_to_add);

job_t * get_welder_job();
void add_welder_job(job_t* work_to_add);

job_t * get_painter_job();
void add_painter_job(job_t* work_to_add);

job_t * get_screwdriver_job();
void add_srewdriver_job(job_t* work_to_add);

job_t * get_milling_job();
void add_milling_job(job_t* work_to_add);

void free_buffers();

#endif //HW06_BUFFERS_H