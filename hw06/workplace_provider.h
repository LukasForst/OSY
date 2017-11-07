//
// Created by lukas on 11/7/17.
//

#include "global.h"

#ifndef HW06_WORKPLACE_PROVIDER_H
#define HW06_WORKPLACE_PROVIDER_H

void delete_workplace(workplace_type type);

void add_workplace(workplace_type type);

workplace_t *get_workplace(workplace_type type);

workplace_type parse_workplace_type(char *type);

void free_workplaces();

#endif //HW06_WORKPLACE_PROVIDER_H
