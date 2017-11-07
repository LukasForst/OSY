#include <stdio.h>

enum work_place_name {SCISSORS, DRILL, BENDING_MACHINE, WELDER, PAINTER, SCREWDRIVER, MILLING_CUTTER};

typedef struct {
    int worker_number;
    char * name;
} worker_data;

typedef struct{
    enum work_place_name name;
    _Bool is_active;
    worker_data ** workers;
} work_place;

void * worker(void * arg){
    worker_data * data = (worker_data*) arg;
    NULL
}

int main() {
    printf("Hello, World!\n");
    return 0;
}