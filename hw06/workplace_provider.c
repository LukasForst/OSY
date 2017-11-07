//
// Created by lukas on 11/7/17.
//

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "workplace_provider.h"

workplace_t *head;

workplace_t *get_workplace(workplace_type type) {
    workplace_t *cursor = head;
    workplace_t *possible_workplace = NULL;

    while (cursor != NULL) {
        if (cursor->type == type) {
            if (cursor->is_working) {
                possible_workplace = cursor;
            } else {
                return cursor;
            }
        }

        cursor = cursor->next_workplace;
    }

    return possible_workplace;
}

workplace_type parse_workplace_type(char *type) {
    if (strcmp("nuzky", type) == 0) {
        return SCISSORS;

    } else if (strcmp("vrtacka", type) == 0) {
        return (DRILL);

    } else if (strcmp("ohybacka", type) == 0) {
        return (BENDING_MACHINE);

    } else if (strcmp("svarecka", type) == 0) {
        return (WELDER);

    } else if (strcmp("lakovna", type) == 0) {
        return (PAINTER);

    } else if (strcmp("sroubovak", type) == 0) {
        return (SCREWDRIVER);

    } else if (strcmp("freza", type) == 0) {
        return (MILLING_CUTTER);

    }

    //todo better error handling
    return (workplace_type) -1;
}

void delete_workplace(workplace_type type) {
    workplace_t *cursor = head;
    workplace_t *previous = cursor;

    while (cursor != NULL) {
        if (cursor->type == type && !cursor->is_working) {
            pthread_mutex_lock(&cursor->mutex);

            if (cursor == head) {
                head = cursor->next_workplace;
            } else {
                previous->next_workplace = cursor->next_workplace;
            }

            cursor->next_workplace = NULL;

            pthread_mutex_unlock(&cursor->mutex);
            pthread_mutex_destroy(&cursor->mutex);
            free(cursor);
            return;
        }

        previous = cursor;
        cursor = cursor->next_workplace;
    }

    cursor = head;
    previous = cursor;
    while (cursor != NULL) {
        if (cursor->type == type) {
            pthread_mutex_lock(&cursor->mutex);//this will wait for running job in the workplace

            previous->next_workplace = cursor->next_workplace;
            cursor->next_workplace = NULL;

            pthread_mutex_unlock(&cursor->mutex);
            pthread_mutex_destroy(&cursor->mutex);
            free(cursor);
            return;
        }

        cursor = cursor->next_workplace;
    }
}

void add_workplace(workplace_type type) {
    workplace_t *new_workplace = (workplace_t *) malloc(sizeof(workplace_t));
    new_workplace->type = type;
    new_workplace->is_working = false;
    new_workplace->is_active = true;
    new_workplace->next_workplace = NULL;

    pthread_mutex_init(&(new_workplace->mutex), NULL);

    if (head == NULL) {
        head = new_workplace;
    } else {
        workplace_t *tail = head;
        while (tail != NULL) {
            if (tail->next_workplace != NULL) {
                tail = tail->next_workplace;
            } else {
                tail->next_workplace = new_workplace;
                break;
            }
        }
    }
}

void free_workplaces() {
    workplace_t *cursor = head;

    while (cursor != NULL) {
        workplace_t *current = cursor;
        cursor = current->next_workplace;

        pthread_mutex_lock(&current->mutex); //this will waits for another job, which is taking place on this workplace
        pthread_mutex_unlock(&current->mutex);
        pthread_mutex_destroy(&current->mutex);
        free(current);
    }
}