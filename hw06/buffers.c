//
// Created by lukas on 11/7/17.
//
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffers.h"

job_t *scissors_head = NULL;
pthread_mutex_t scissors_mutex;

job_t *drill_head = NULL;
pthread_mutex_t drill_mutex;

job_t *bending_machine_head = NULL;
pthread_mutex_t bending_machine_mutex;

job_t *welder_head = NULL;
pthread_mutex_t welder_mutex;

job_t *painter_head = NULL;
pthread_mutex_t painter_mutex;

job_t *screwdriver_head = NULL;
pthread_mutex_t screwdriver_mutex;

job_t *milling_cutter_head = NULL;
pthread_mutex_t milling_cutter_mutex;


_Bool contains_job_in_stage(workplace_type workplace_type) {
    switch (workplace_type) {
        case SCISSORS:
            return scissors_head != NULL;
        case DRILL:
            return drill_head != NULL;
        case BENDING_MACHINE:
            return bending_machine_head != NULL;
        case WELDER:
            return welder_head != NULL;
        case PAINTER:
            return painter_head != NULL;
        case SCREWDRIVER:
            return screwdriver_head != NULL;
        case MILLING_CUTTER:
            return milling_cutter_head != NULL;
        default:
            return false;
    }
}

job_t *get_tail(job_t *head) {
    job_t *cursor = head;
    while (cursor != NULL) {
        if (cursor->next_job != NULL) {
            cursor = cursor->next_job;
        } else {
            break;
        }
    }
    return cursor;
}

void free_one_buffer(job_t *head) {
    while (head != NULL) {
        job_t *to_free = head;
        head = head->next_job;
        free(to_free);
    }
}

void free_buffers() {
    free_one_buffer(scissors_head);
    free_one_buffer(drill_head);
    free_one_buffer(bending_machine_head);
    free_one_buffer(welder_head);
    free_one_buffer(painter_head);
    free_one_buffer(screwdriver_head);
    free_one_buffer(milling_cutter_head);

    scissors_head = NULL;
    drill_head = NULL;
    bending_machine_head = NULL;
    welder_head = NULL;
    painter_head = NULL;
    screwdriver_head = NULL;
    milling_cutter_head = NULL;
}

void buffers_init() {
    pthread_mutex_init(&scissors_mutex, NULL);
    pthread_mutex_init(&drill_mutex, NULL);
    pthread_mutex_init(&bending_machine_mutex, NULL);
    pthread_mutex_init(&welder_mutex, NULL);
    pthread_mutex_init(&painter_mutex, NULL);
    pthread_mutex_init(&screwdriver_mutex, NULL);
    pthread_mutex_init(&milling_cutter_mutex, NULL);
}

job_t *get_generic_job(job_t **head, pthread_mutex_t *mutex) {
    if (*head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(mutex);

    job_t *cursor = *head;
    job_t *previous = *head;
    job_t *result = *head;

    while (cursor->next_job != NULL) {
        if (result->step > cursor->next_job->step) {
            result = cursor->next_job;
            previous = cursor;
        } else if (result->step == cursor->next_job->step) {
            if (result->type > cursor->next_job->type) {
                result = cursor->next_job;
                previous = cursor;
            }

        }
        cursor = cursor->next_job;
    }

    if (result == *head) {
        (*head) = NULL;
    } else if (previous == *head) {
        (*head)->next_job = result->next_job;
    } else {
        previous->next_job = result->next_job;
    }

    pthread_mutex_unlock(mutex);
    return result;
}


job_t *get_scissors_job() {
    return get_generic_job(&scissors_head, &scissors_mutex);
}

void add_scissors_job(job_t *work_to_add) {
    pthread_mutex_lock(&scissors_mutex);

    job_t *tail = get_tail(scissors_head);
    if (tail == NULL) {
        scissors_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&scissors_mutex);
}

job_t *get_drill_job() {
    return get_generic_job(&drill_head, &drill_mutex);
}

void add_drill_job(job_t *work_to_add) {
    pthread_mutex_lock(&drill_mutex);

    job_t *tail = get_tail(drill_head);
    if (tail == NULL) {
        drill_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&drill_mutex);
}

job_t *get_bending_machine_job() {
    return get_generic_job(&bending_machine_head, &bending_machine_mutex);
}

void add_bending_machine_job(job_t *work_to_add) {
    pthread_mutex_lock(&bending_machine_mutex);

    job_t *tail = get_tail(bending_machine_head);
    if (tail == NULL) {
        bending_machine_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&bending_machine_mutex);

}

job_t *get_welder_job() {
    return get_generic_job(&welder_head, &welder_mutex);
}

void add_welder_job(job_t *work_to_add) {
    pthread_mutex_lock(&welder_mutex);

    job_t *tail = get_tail(welder_head);
    if (tail == NULL) {
        welder_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }
    pthread_mutex_unlock(&welder_mutex);

}

job_t *get_painter_job() {
    return get_generic_job(&painter_head, &painter_mutex);
}

void add_painter_job(job_t *work_to_add) {
    pthread_mutex_lock(&painter_mutex);

    job_t *tail = get_tail(painter_head);
    if (tail == NULL) {
        painter_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&painter_mutex);

}

job_t *get_screwdriver_job() {
    return get_generic_job(&screwdriver_head, &screwdriver_mutex);
}

void add_screwdriver_job(job_t *work_to_add) {
    pthread_mutex_lock(&screwdriver_mutex);

    job_t *tail = get_tail(screwdriver_head);
    if (tail == NULL) {
        screwdriver_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&screwdriver_mutex);

}

job_t *get_milling_job() {
    return get_generic_job(&milling_cutter_head, &milling_cutter_mutex);
}

void add_milling_job(job_t *work_to_add) {
    pthread_mutex_lock(&milling_cutter_mutex);

    job_t *tail = get_tail(milling_cutter_head);
    if (tail == NULL) {
        milling_cutter_head = work_to_add;
    } else {
        tail->next_job = work_to_add;
    }

    pthread_mutex_unlock(&milling_cutter_mutex);

}