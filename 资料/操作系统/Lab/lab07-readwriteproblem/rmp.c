#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

pthread_t t1,t2,t3;
sem_t full_b1,empty_b1,full_b2,empty_b2;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void reader(void* arg);
void writer(void* arg);
void printer(void* arg);

char fruit[5][10] = {"Applbe","Banana","cherry","fig","grape"};
char B1[20]="";
char B2[20]="";

int main(){
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    sem_init(&empty_b1,0,1);
    sem_init(&full_b1,0,0);
    sem_init(&empty_b2,0,0);
    sem_init(&full_b2,0,1);
    pthread_create(&t1,NULL,reader,NULL);
    pthread_create(&t2,NULL,writer,NULL);
    pthread_create(&t3,NULL,printer,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    sem_destroy(&empty_b1);
    sem_destroy(&empty_b2);
    sem_destroy(&full_b1);
    sem_destroy(&full_b2);
    return 0;
}

void reader(void* arg){
    int i;
    for(i = 0;i < 20; i++){
        sem_wait(&empty_b1);
        pthread_mutex_lock(&mutex1);
        strcpy(B1,fruit[i%5]);
        printf("read is work %d : %s\n",i%5,fruit[i%5]);
        pthread_mutex_unlock(&mutex1);
        sem_post(&full_b1);
    }
}

void writer(void* arg){
    int i;
    for(i=0;i<20;i++){
        sem_wait(&full_b1);
        sem_wait(&full_b2);
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        strcpy(B2,B1);
        printf("move is work %d : %s\n",i%5,B2);
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
        sem_post(&empty_b2);
        sem_post(&empty_b1);
    }
}

void printer(void* arg){
    int i;
    for(i=0;i<20;i++){
        sem_wait(&empty_b2);
        pthread_mutex_lock(&mutex2);
        printf("print is work %d : %s\n",i%5,B2);
        pthread_mutex_unlock(&mutex2);
        sem_post(&full_b2);
    }
}