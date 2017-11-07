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

void *worker(void *arg) {
    worker_info_t *worker_info = (worker_info_t *) arg;
    workplace_t *workplace = worker_info->workplace;

    while (true) {
        job_t *job = get_job(workplace->type);

        if (job == NULL) {
            sem_wait(&workplace->added);
            continue;
        }

        pthread_mutex_lock(&workplace->mutex);

        worker_info->is_active = true;
        worker_info->workplace->is_active = true;

        printf("%s %s %c %d\n", worker_info->name, get_workplace_name(workplace->type), get_job_type_name(job->type),
               job->step);
        usleep((__useconds_t) job->sleep_time);

        workplace_type next_workplace_type = get_next_workplace_type(job);
        if (next_workplace_type == FINISHED) {
            printf("done %c\n", get_job_type_name(job->type));
            free(job);
        }

        pthread_mutex_unlock(&workplace->mutex);
        break;
    }


    return NULL;
}