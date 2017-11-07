//
// Created by lukas on 11/7/17.
//

#include "global.h"

#ifndef HW06_WORKPLACE_PROVIDER_H
#define HW06_WORKPLACE_PROVIDER_H

void remove_workplace(char* type);
void create_workplace(char* type);

workplace_t * get_workplace(workplace_type type);

void free_workplaces();

#endif //HW06_WORKPLACE_PROVIDER_H
