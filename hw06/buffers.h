//
// Created by lukas on 11/7/17.
//

#ifndef HW06_BUFFERS_H
#define HW06_BUFFERS_H

typedef struct work{
    int id;
    char name;
    struct work * next_work;
} work_t;

void init();

work_t * get_scissors_job();
void add_scissors_job(work_t* work_to_add);

work_t * get_drill_job();
void add_drill_job(work_t* work_to_add);

work_t * get_bending_machine_job();
void add_bending_machine_job(work_t* work_to_add);

work_t * get_welder_job();
void add_welder_job(work_t* work_to_add);

work_t * get_painter_job();
void add_painter_job(work_t* work_to_add);

work_t * get_screwdriver_job();
void add_srewdriver_job(work_t* work_to_add);

work_t * get_milling_job();
void add_milling_job(work_t* work_to_add);


#endif //HW06_BUFFERS_H
