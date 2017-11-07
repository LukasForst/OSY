//
// Created by lukas on 11/7/17.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "workplace_chain.h"
#include "workplace_provider.h"
#include "job_provider.h"

_Bool command_make() {
    char char_type;
    if (scanf(" %c", &char_type) != 1) {
        //todo error handling
        return false;
    }
    job_t *job = create_job(char_type);
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
    char *workplace_name;
    if (scanf("%ms", &workplace_name) != 1) {
        //todo error handling
        return false;
    }
    workplace_type type = parse_workplace_type(workplace_name);
    add_workplace(type);
    free(workplace_name);
    return true;
}

_Bool command_remove() {
    char *workplace_name;
    if (scanf("%ms", &workplace_name) != 1) {
        //todo error handling
        return false;
    }
    workplace_type type = parse_workplace_type(workplace_name);
    delete_workplace(type);
    free(workplace_name);
    return true;
}