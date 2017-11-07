//
// Created by lukas on 11/7/17.
//

#ifndef HW06_FACTORY_H
#define HW06_FACTORY_H

#include "global.h"


void add_job(workplace_name name, job_t * work_to_add);
job_t * get_job(workplace_name name);

#endif //HW06_FACTORY_H
