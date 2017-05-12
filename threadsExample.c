#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

pthread_t tid[3];

void* startProcessing(void *arg){

    unsigned long i = 0;
    pthread_t id = pthread_self();
    FILE *file;
    file = fopen("testFile.txt", "wt");
    char *  result;
    if(pthread_equal(id,tid[0])){
        printf("\n First thread processing\n");

    }
    else if(pthread_equal(id,tid[1])){
        printf("\n Second thread processing\n");
    }
    else{
        printf("\n Third thread processing\n");
    }

    if (file == NULL){
        printf("File creation error\n");
        return;
    }
    result = fputs("File creation success", file);
    if (result == EOF){
        printf("Error on write\n");
    }
    fclose(file);

}

int main(void)
{
    int i = 0;
    int cThread;

    while(i < 3)
    {
        cThread = pthread_create(&(tid[i]), NULL, &startProcessing, NULL);
        if (cThread != 0)
            printf("\ncan't create thread :[%s]", strerror(cThread));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}
