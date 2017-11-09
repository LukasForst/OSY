#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#include "buffers.h"
#include "commands.h"
#include "workplace_provider.h"
#include "worker_provider.h"

int main() {
    buffers_init();
    sem_init(&producer_wake, 1, 0);

    int scan_result;
    char *word;
    scan_result = scanf("%ms", &word);
    while (true) {
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
            free(word);
            word = NULL;
            scan_result = scanf("%ms", &word);
        }

        if (word != NULL) {
            free(word);
            word = NULL;
        }

        if (scan_result != EOF) {
            continue;
        }
        break;
    }

    free_workers();
    free_buffers();
    free_workplaces();
    return 0;
}