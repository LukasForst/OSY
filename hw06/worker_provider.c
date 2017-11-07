//
// Created by lukas on 11/7/17.
//
#include "worker_provider.h"

#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "worker.h"

typedef struct running_worker {
    pthread_t thread;
    char *worker_name;
    struct running_worker *next;
} running_worker_t;

running_worker_t *head;

pthread_t create_worker(char *name, workplace_t *workplace) {
    worker_info_t *worker_info = (worker_info_t *) malloc(sizeof(worker_info_t));

    worker_info->name = (char *) malloc((strlen(name) + 3) * sizeof(char));
    strcpy(worker_info->name, name);

    worker_info->workplace = workplace;
    worker_info->is_active = false;

    pthread_t thread;
    pthread_create(&thread, NULL, worker, (void *) worker_info);

    running_worker_t *running = (running_worker_t *) malloc(sizeof(running_worker_t));
    running->next = NULL;
    running->thread = thread;
    running->worker_name = (char *) malloc((strlen(name) + 3) * sizeof(char));
    strcpy(running->worker_name, name);


    if (head == NULL) {
        head = running;
    } else {
        running_worker_t *cursor = head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = running;
    }
    return thread;
}

void remove_worker(char *name) {
    running_worker_t *cursor = head;
    running_worker_t *previous = cursor;

    while (cursor != NULL) {
        if (strcmp(name, cursor->worker_name) == 0) {
            //todo wake up worker
            pthread_join(cursor->thread, NULL);

            if (cursor == head) {
                head = cursor->next;
            } else {
                previous->next = cursor->next;
            }
            cursor->next = NULL;

            free(cursor->worker_name);
            free(cursor);
            return;
        }
        previous = cursor;
        cursor = cursor->next;
    }
    fprintf(stderr, "No worker was removed because \"%s\" does not exist!\n", name);
}

void free_workers() {
    running_worker_t *cursor = head;
    while (cursor != NULL) {
        running_worker_t *to_be_freed = cursor;
        cursor = cursor->next;
        //todo wake up worker
        pthread_join(to_be_freed->thread, NULL);
        free(to_be_freed);
    }
}