//
// Created by lukas on 11/7/17.
//
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include "buffers.h"

work_t *scissors_head;
pthread_mutex_t scissors_mutex;

work_t *drill_head;
pthread_mutex_t drill_mutex;

work_t *bending_machine_head;
pthread_mutex_t bending_machine_mutex;

work_t *welder_head;
pthread_mutex_t welder_mutex;

work_t *painter_head;
pthread_mutex_t painter_mutex;

work_t *screwdriver_head;
pthread_mutex_t screwdriver_mutex;

work_t *milling_cutter_head;
pthread_mutex_t milling_cutter_mutex;


work_t *get_tail(work_t *head) {
    while (head != NULL) {
        if (head->next_work != NULL) {
            head = head->next_work;
        } else {
            return head;
        }
    }
    return head;
}

void init() {
    pthread_mutex_init(&scissors_mutex, NULL);
    pthread_mutex_init(&drill_mutex, NULL);
    pthread_mutex_init(&bending_machine_mutex, NULL);
    pthread_mutex_init(&welder_mutex, NULL);
    pthread_mutex_init(&painter_mutex, NULL);
    pthread_mutex_init(&screwdriver_mutex, NULL);
    pthread_mutex_init(&milling_cutter_mutex, NULL);
}

work_t *get_scissors_job() {
    if (scissors_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&scissors_mutex);

    work_t *result = scissors_head;
    scissors_head = scissors_head->next_work;

    pthread_mutex_unlock(&scissors_mutex);
    return result;
}

void add_scissors_job(work_t *work_to_add) {
    pthread_mutex_lock(&scissors_mutex);

    work_t *tail = get_tail(scissors_head);
    if (tail == NULL) {
        scissors_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&scissors_mutex);
}

work_t *get_drill_job() {
    if (drill_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&drill_mutex);

    work_t *result = drill_head;
    drill_head = drill_head->next_work;

    pthread_mutex_unlock(&drill_mutex);
    return result;
}

void add_drill_job(work_t *work_to_add) {
    pthread_mutex_lock(&drill_mutex);

    work_t *tail = get_tail(drill_head);
    if (tail == NULL) {
        drill_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&drill_mutex);
}

work_t *get_bending_machine_job() {
    if (bending_machine_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&bending_machine_mutex);

    work_t *result = bending_machine_head;
    bending_machine_head = bending_machine_head->next_work;

    pthread_mutex_unlock(&bending_machine_mutex);
    return result;
}

void add_bending_machine_job(work_t *work_to_add) {
    pthread_mutex_lock(&bending_machine_mutex);

    work_t *tail = get_tail(bending_machine_head);
    if (tail == NULL) {
        bending_machine_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&bending_machine_mutex);

}

work_t *get_welder_job() {
    if (welder_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&welder_mutex);

    work_t *result = welder_head;
    welder_head = welder_head->next_work;

    pthread_mutex_unlock(&welder_mutex);
    return result;
}

void add_welder_job(work_t *work_to_add) {
    pthread_mutex_lock(&welder_mutex);

    work_t *tail = get_tail(welder_head);
    if (tail == NULL) {
        welder_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }
    pthread_mutex_unlock(&welder_mutex);

}

work_t *get_painter_job() {
    if (painter_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&painter_mutex);

    work_t *result = painter_head;
    painter_head = painter_head->next_work;

    pthread_mutex_unlock(&painter_mutex);
    return result;
}

void add_painter_job(work_t *work_to_add) {
    pthread_mutex_lock(&painter_mutex);

    work_t *tail = get_tail(painter_head);
    if (tail == NULL) {
        painter_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&painter_mutex);

}

work_t *get_screwdriver_job() {
    if (screwdriver_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&screwdriver_mutex);

    work_t *result = screwdriver_head;
    screwdriver_head = screwdriver_head->next_work;

    pthread_mutex_unlock(&screwdriver_mutex);
    return result;
}

void add_srew_driver_job(work_t *work_to_add) {
    pthread_mutex_lock(&screwdriver_mutex);

    work_t *tail = get_tail(screwdriver_head);
    if (tail == NULL) {
        screwdriver_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&screwdriver_mutex);

}

work_t *get_milling_job() {
    if (milling_cutter_head == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&milling_cutter_mutex);

    work_t *result = milling_cutter_head;
    milling_cutter_head = milling_cutter_head->next_work;

    pthread_mutex_unlock(&milling_cutter_mutex);
    return result;
}

void add_milling_job(work_t *work_to_add) {
    pthread_mutex_lock(&milling_cutter_mutex);

    work_t *tail = get_tail(milling_cutter_head);
    if (tail == NULL) {
        milling_cutter_head = work_to_add;
    } else {
        tail->next_work = work_to_add;
    }

    pthread_mutex_unlock(&milling_cutter_mutex);

}