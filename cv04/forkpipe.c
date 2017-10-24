#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

void gen(int *pipe);

void nsd(int *pipe);


int main(int argc, char *argv[]) {
    pid_t pid, GEN;
    int fd[2];

    if (pipe(fd)) {
        fprintf(stderr, "ERROR");
        return 2;
    }

    pid = fork();

    if (pid == (pid_t) 0) { //GEN
        gen(fd);

    } else if (pid < (pid_t) 0) {
        fprintf(stderr, "ERROR");
        return 2;

    } else {
        GEN = pid;
        pid = fork();

        if (pid == (pid_t) 0) { //NSD
            nsd(fd);
        } else if (GEN < (pid_t) 0) {
            fprintf(stderr, "ERROR");
            return 2;
        } else { //parent
            close(fd[0]);
            close(fd[1]);

            sleep(5);

            kill(GEN, SIGTERM);

            int status;
            waitpid(GEN, &status, WUNTRACED);
        }
    }

    return 0;
}

void nsd(int *pipe) {
    dup2(pipe[READ_END], STDIN_FILENO);

    execl("./nsd", "./nsd", (char *) NULL);
}

volatile sig_atomic_t done = 0;

void term(int signum) {
    done = 1;
}

void gen(int *pipe) {
    dup2(pipe[WRITE_END], STDOUT_FILENO);

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    sigemptyset(&action.sa_mask);
    action.sa_handler = term;
    action.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGTERM, &action, NULL);

    while (!done) {
        printf("%d %d\n", rand(), rand());
        sleep(1);
    }

    close(pipe[WRITE_END]);
    fprintf(stderr, "GEN TERMINATED\n");
}