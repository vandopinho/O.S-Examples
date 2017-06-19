#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>


void handler ( void *ptr );

sem_t mutex;
int counter =0;

int main(){
    int i[3];
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;
    i[0] = 0;
    i[1] = 1;
    i[2] = 2;
    sem_init(&mutex, 0, 1);
    pthread_create (&thread_a, NULL, (void *) &handler, (void *) &i[0]);
    pthread_create (&thread_b, NULL, (void *) &handler, (void *) &i[1]);
    pthread_create (&thread_c, NULL, (void *) &handler, (void *) &i[2]);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    sem_destroy(&mutex);
    exit(0);
}

void handler ( void *ptr ){
    int x;
    FILE *file;
    file = fopen("testFile.txt", "w");
    fclose(file);
    char *  result;
    x = *((int *) ptr);
    printf("Thread %d: Waiting to enter critical region...\n", x);
    sem_wait(&mutex);
    printf("Thread %d: Now in critical region...\n", x);
    file = fopen("testFile.txt", "a+");
    if (file == NULL){
        printf("File creation error\n");
        return;
    }
    if (counter == 0){
        result = fputs("Thread 1: Writed on the file \n", file);
    }
    if (counter == 1){
        result = fputs("Thread 2: Writed on the file \n", file);
    }
    if (counter == 2){
      result = fputs("Thread 3: Writed on the file\n", file);
    }
    if (result == EOF){
        printf("Error on write\n");
    }
    fclose(file);
    counter++;
    printf("Thread %d: Exiting critical region...\n", x);
    sem_post(&mutex);
    pthread_exit(0);
}
