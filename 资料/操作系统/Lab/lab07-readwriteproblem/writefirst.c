#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
int rcount = 0;
int wcount = 0;
sem_t writemutex;
sem_t readmutex;
sem_t mutex1;
sem_t mutex2;
sem_t z;
struct timeval dwStart;
struct timeval dwAfter;
struct timeval dwBefore;
struct timeval dwAfter_w;
struct timeval dwBefore_w;
unsigned long diff;
pthread_t t1[100];
pthread_t t2[60];
void* writer(void *arg);
void* reader(void *arg);
int main()
{   int i=0;
    int j=0;
    sem_init(&writemutex,0,1);
    sem_init(&readmutex,0,1);
    sem_init(&mutex1,0,1);
    sem_init(&mutex2,0,1);
    sem_init(&z,0,1);
    gettimeofday(&dwStart,NULL);
    int cnt = 0;
    for(cnt=0;cnt<20;cnt++){
        for(i=0;i<5;i++){
        pthread_create(&t1[cnt*5+i],NULL,(void*)reader,NULL);
        }
        for(j=0;j<3;j++){
        pthread_create(&t2[cnt*3+j],NULL,(void*)writer,NULL);
        }
    }
    for(cnt=0;cnt<20;cnt++){
        for(i=0;i<5;i++){
        pthread_join(t1[cnt*5+i],NULL);
        }for(j=0;j<3;j++){
        pthread_join(t2[cnt*3+i],NULL);
    }
    }
    return 0;

}
void* writer(void *arg){
        gettimeofday(&dwBefore_w,NULL);
        sem_wait(&mutex2);
        wcount++;
        if(wcount==1)
            sem_wait(&readmutex);
        sem_post(&mutex2);
        sem_wait(&writemutex);
        long pid = pthread_self();
        gettimeofday(&dwAfter_w,NULL);
        printf("pid %ld,\tw,\t%f,\t%f\n",pid,
        (float)((dwBefore_w.tv_sec-dwStart.tv_sec)+ dwBefore_w.tv_usec-dwStart.tv_usec)/(float)1000000,
        (float)((dwAfter_w.tv_sec-dwStart.tv_sec)+ dwAfter_w.tv_usec-dwStart.tv_usec)/(float)1000000);
        sem_post(&writemutex);
        sem_wait(&mutex2);
        wcount--;
        if(wcount==0)
            sem_post(&readmutex);
        sem_post(&mutex2);
}
void* reader(void *arg){
        gettimeofday(&dwBefore,NULL);
        sem_wait(&z);
        sem_wait(&readmutex);
        sem_wait(&mutex1);
        rcount++;
        if(rcount==1)
        sem_wait(&writemutex);
        sem_post(&mutex1);
        sem_post(&readmutex);
        sem_post(&z);
        long pid = pthread_self();
        gettimeofday(&dwAfter,NULL);
        printf("pid %ld,\tr,\t%f,\t%f\n",pid,(float)((dwBefore.tv_sec-dwStart.tv_sec)+ dwBefore.tv_usec-dwStart.tv_usec)/(float)1000000, (float)((dwAfter.tv_sec-dwStart.tv_sec)+ dwAfter.tv_usec-dwStart.tv_usec)/(float)1000000);
        sem_wait(&mutex1);
        rcount--;
        if(rcount == 0)
            sem_post(&writemutex);
        sem_post(&mutex1);
}