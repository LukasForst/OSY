//
// Created by lukas on 11/7/17.
//

#include "global.h"

/*

A: 1:nuzky   - 2:vrtacka - 3:ohybacka  - 4:svarecka - 5:vrtacka - 6:lakovna
B: 1:vrtacka - 2:nuzky   - 3:freza     - 4:vrtacka  - 5:lakovna - 6:sroubovak
C: 1:freza   - 2:vrtacka - 3:sroubovak - 4:vrtacka  - 5:freza   - 6:lakovna

*/

workplace_name A_chain[6] = {SCISSORS, DRILL, BENDING_MACHINE, WELDER, DRILL, PAINTER};
workplace_name B_chain[6] = {DRILL, SCISSORS, MILLING_CUTTER, DRILL, PAINTER, SCREWDRIVER};
workplace_name C_chain[6] = {MILLING_CUTTER, DRILL, SCREWDRIVER, DRILL, MILLING_CUTTER, PAINTER};


workplace_name get_next(workplace_name name, workplace_name *chain, int chain_size) {
    for (int i = 0; i < chain_size; i++) {
        if (name == chain[i]) {
            return ++i >= chain_size ? FINISHED : chain[i];
        }
    }

    return FINISHED;
}


workplace_name get_next_work_place(job_t *job) {
    switch (job->type) {
        case A:
            return get_next(job->current_place, A_chain, sizeof(A_chain));
        case B:
            return get_next(job->current_place, B_chain, sizeof(B_chain));
        case C:
            return get_next(job->current_place, C_chain, sizeof(C_chain));
    }
    return FINISHED;
}


