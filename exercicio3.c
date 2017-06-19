#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int TAM = 50;
int tickets[50];
int ticketRead[50];
int ticketStart = 1;

void *createTicket (){
    int i;
    for(i = 0; i < TAM; i++, ticketStart++){
        tickets[i] = ticketStart;
        printf("Created ticket: %d\n", tickets[i]);
    }
}

void *readTicket(){
    int j;
    for(j = 0; j < TAM;){
        if(tickets[j] != 0){
            ticketRead[j] = tickets[j];
            printf("Ticket read: %d\n", ticketRead[j]);
            j++;
        }

    }
}

int main(){
    int k;
    for(k = 0; k < TAM; k++){
        tickets[k] = 0;
    }
    pthread_t creatingTicket;
    pthread_t readingTicket;
    pthread_create(&creatingTicket, NULL, createTicket, NULL);
    pthread_create(&readingTicket, NULL, readTicket, NULL);
    pthread_join(readingTicket, NULL);
    return 1;
}
