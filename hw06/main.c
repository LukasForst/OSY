#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#include "buffers.h"
#include "commands.h"

void *worker(void *arg) {
    worker_t *data = (worker_t *) arg;

    return NULL;
}

_Bool should_read = true;

int main() {
    buffers_init();

    int scan_result;
    char *word;
    scan_result = scanf("%ms", &word);
    while (should_read) {
        while (scan_result == 1) {

            if (strcmp(word, "make") == 0) {
                command_make();
            } else if (strcmp(word, "start") == 0) {
                command_start();
            } else if (strcmp(word, "end") == 0) {
                command_end();
            } else if (strcmp(word, "add") == 0) {
                command_add();
            } else if (strcmp(word, "remove") == 0) {
                command_remove();
            }

            scan_result = scanf("%ms", &word);
        }

        if (scan_result != EOF) {
            if (word != NULL) {
//                free(word);
            }
            continue;
        }

        //todo free data and wait for consumers
    }

    return 0;
}