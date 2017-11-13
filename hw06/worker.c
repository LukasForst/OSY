//
// Created by lukas on 11/7/17.
//

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#include "worker.h"
#include "global.h"
#include "job_provider.h"
#include "workplace_provider.h"
#include "workplace_chain.h"
pthread_mutex_t printing_mutex;

void *worker(void *arg) {
    worker_info_t *worker_info = (worker_info_t *) arg;
    fprintf(stderr, "Worker \"%s\" started!\n", worker_info->name);
    sem_post(&producer_wake);

    while (worker_info->is_active) {
        job_t *job = get_job(worker_info->type);
        if (job == NULL) {
            fprintf(stderr, "Worker \"%s\" is waiting!\n", worker_info->name);
            sem_wait(&worker_info->wakeup);
            fprintf(stderr, "Worker \"%s\" woke up!\n", worker_info->name);
            continue;
        }
        worker_info->is_working = true;

        fprintf(stderr, "Worker \"%s\" is looking for workplace type \"%s\".\n", worker_info->name, get_workplace_name(worker_info->type));
        workplace_t * workplace = get_workplace(worker_info->type);

        fprintf(stderr, "Worker \"%s\" is waiting for workplace \"%s\"!\n", worker_info->name, get_workplace_name(workplace->type));
        pthread_mutex_lock(&workplace->mutex);
        fprintf(stderr, "Worker \"%s\" is going to work!\n", worker_info->name);

        workplace->is_working = true;

        pthread_mutex_lock(&printing_mutex);
        printf("%s %s %c %d\n", worker_info->name, get_workplace_name(workplace->type), get_job_type_name(job->type),
               job->step);
        pthread_mutex_unlock(&printing_mutex);
        usleep(job->sleep_time);

        workplace_type next_workplace_type = get_next_workplace_type(job);
        if (next_workplace_type == FINISHED) {
            pthread_mutex_lock(&printing_mutex);
            printf("done %c\n", get_job_type_name(job->type));
            pthread_mutex_unlock(&printing_mutex);
            free(job);
        } else {
            job->previous_workplace = job->current_workplace;
            job->current_workplace = next_workplace_type;
            job->sleep_time = get_sleep_time(next_workplace_type);
            job->step++;
            add_job(job);
        }

        worker_info->is_working = false;
        workplace->is_working = false;
        pthread_mutex_unlock(&workplace->mutex);
        sem_post(&producer_wake);
    }
    return NULL;
}