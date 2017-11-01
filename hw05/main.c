#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include<semaphore.h>

#define DEFAULT_CONSUMERS 1

pthread_mutex_t print_mutex, buffer_mutex;
sem_t wake_consumer, wake_producer;

int number_of_consumers = DEFAULT_CONSUMERS;

typedef struct node {
    char * word;
    unsigned int id;

    struct node *next;
} node_s;

node_s * head;

void write_to_buffer(char*data, unsigned int id) {
    node_s * node = (node_s*)malloc(sizeof(node_s));
    node->word = data;
    node->id = id;
    node->next=NULL;

    if(head == NULL){
        head = node;
    } else{
        node_s * cursor = head;
        while(cursor->next != NULL){
            cursor = cursor->next;
        }
        cursor->next = node;
    }
}

node_s * read_from_buffer(){
    if(head != NULL){
        node_s * result = head;
        if(head->next != NULL){
            head = head->next;
        } else{
            head = NULL;
        }
        return result;
    }

    return NULL;
}

volatile _Bool producer_is_running = true;
volatile _Bool consumer_is_runing = true;

void *producer(void *arg) {
    char * word = (char*) malloc(256*sizeof(char));
    unsigned int id;

    while(producer_is_running){
        int scan_result;
        scan_result = scanf("%u %s", &id, word);

        while(scan_result == 2){
            pthread_mutex_lock(&buffer_mutex);
            write_to_buffer(word, id);
            pthread_mutex_unlock(&buffer_mutex);

            sem_post(&wake_consumer);

            word = (char*) malloc(256*sizeof(char));
            scan_result = scanf("%u %s", &id, word);
        }

        if(scan_result == EOF){
            free(word);
            word = NULL;
            break;
        }
    }

    while(head != NULL){
        sem_wait(&wake_producer);
    }

    consumer_is_runing = false;
    producer_is_running = false;

    for(int i = 0; i <number_of_consumers; i++){
        sem_post(&wake_consumer);
    }
    return NULL;
}

void consume(int consumer_id){
    pthread_mutex_lock(&buffer_mutex);
    node_s * node = read_from_buffer();
    pthread_mutex_unlock(&buffer_mutex);

    if(node != NULL){
        pthread_mutex_lock(&print_mutex);
        printf("Thread %d:", consumer_id);
        for(int i = 0; i < node->id; i++){
            printf(" %s", node->word);
        }
        printf("\n");
        pthread_mutex_unlock(&print_mutex);


        pthread_mutex_lock(&buffer_mutex);
        if(node->word != NULL){
            free(node->word);
            node->word = NULL;
        }

        free(node);
        node = NULL;
        pthread_mutex_unlock(&buffer_mutex);
    }

}

void *consumer(void *arg) {
    int * consumer_id = (int*) arg;
    while(consumer_is_runing){
        while (head != NULL){
            consume(*consumer_id);
        }
        sem_post(&wake_producer);
        sem_wait(&wake_consumer);
    }
    return NULL;
}



void verify_argc(int argc) {
    if (sysconf(_SC_NPROCESSORS_ONLN) < argc || argc < 1) {
        exit(1);
    }
}

int parse_int(char *argv) {
    char *p;
    int num;

    errno = 0;
    long conv = strtol(argv, &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX) {
        fprintf(stderr, "Wrong argument!\n");
        exit(1);
    } else {
        num = (int) conv;
    }

    return num;
}


int main_program(int consumers_no){
    number_of_consumers = consumers_no;

    pthread_t tid_producer;
    pthread_t * tid_consumers = (pthread_t*)malloc(sizeof(pthread_t) * consumers_no);

    pthread_create(&tid_producer,NULL,producer,NULL);


    for (int i = 0; i < consumers_no; i++) {
        int cons_id = i + 1;
        pthread_create(&tid_consumers[i],NULL,consumer,(void*) &cons_id);
    }

    pthread_join(tid_producer, NULL);
    for(int i = 0; i < consumers_no; i++){
        pthread_join(tid_consumers[i], NULL);
    }

    while(head != NULL){
        node_s * to_free = head;
        head = head->next;

        if(to_free->word != NULL){
            free(to_free->word);
        }

        free(to_free);
    }

    free(tid_consumers);
    return 0;
}

int main(int argc, char **argv) {
    pthread_mutex_init(&print_mutex,NULL);
    pthread_mutex_init(&buffer_mutex,NULL);

    sem_init(&wake_consumer,1,0);
    sem_init(&wake_producer,1,1);

    int consumers_no = argc == 1 ? DEFAULT_CONSUMERS : parse_int(argv[1]);
    verify_argc(consumers_no);
    return main_program(consumers_no);
}