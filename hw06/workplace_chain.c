//
// Created by lukas on 11/7/17.
//

#include "global.h"

/*

A: 1:nuzky   - 2:vrtacka - 3:ohybacka  - 4:svarecka - 5:vrtacka - 6:lakovna
B: 1:vrtacka - 2:nuzky   - 3:freza     - 4:vrtacka  - 5:lakovna - 6:sroubovak
C: 1:freza   - 2:vrtacka - 3:sroubovak - 4:vrtacka  - 5:freza   - 6:lakovna

*/

workplace_type A_chain[6] = {SCISSORS, DRILL, BENDING_MACHINE, WELDER, DRILL, PAINTER};
workplace_type B_chain[6] = {DRILL, SCISSORS, MILLING_CUTTER, DRILL, PAINTER, SCREWDRIVER};
workplace_type C_chain[6] = {MILLING_CUTTER, DRILL, SCREWDRIVER, DRILL, MILLING_CUTTER, PAINTER};


workplace_type get_next(workplace_type current_workplace, workplace_type *chain, int chain_size) {
    if(current_workplace == NOT_STARTED){
        return chain[0];
    }

    for (int i = 0; i < chain_size; i++) {
        if (current_workplace == chain[i]) {
            return ++i >= chain_size ? FINISHED : chain[i];
        }
    }

    return FINISHED;
}


workplace_type get_next_work_place(job_t *job) {
    switch (job->type) {
        case A:
            return get_next(job->current_workplace, A_chain, sizeof(A_chain));
        case B:
            return get_next(job->current_workplace, B_chain, sizeof(B_chain));
        case C:
            return get_next(job->current_workplace, C_chain, sizeof(C_chain));
        default:
            return FINISHED;
    }
}


/*
nuzky: 100
vrtacka: 200
ohybacka: 150
svarecka: 300
lakovna: 400
sroubovak: 250
freza: 500
*/

int get_sleep_time(workplace_type current_workplace){
    switch (current_workplace){
        case SCISSORS:
            return 100;
        case DRILL:
            return 200;
        case BENDING_MACHINE:
            return 150;
        case WELDER:
            return 300;
        case PAINTER:
            return 400;
        case SCREWDRIVER:
            return 250;
        case MILLING_CUTTER:
            return 500;
        default:
            return 0;
    }
}