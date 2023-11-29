#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "buffer.h"
#include "buffer.c"


//extern

sem_t empty,full;               
pthread_mutex_t mutex;  
        
void *producer( void *arg );    //生产者线程
void *consumer( void *arg );    //消费者线程

int main(int argc , char *argv[]){
    pthread_t thrd_prod , thrd_cons;
 
    srand(time(NULL));

    sem_init(&empty, 0, 5); 
    sem_init(&full, 0, 0); 
    sem_init(&mutex, 0, 1); 
    srand(time(NULL));
    
    if( pthread_create( &thrd_prod , NULL, producer ,NULL ) != 0 )
        printf( "thread create failed." );

    if( pthread_create( &thrd_cons , NULL, consumer ,NULL ) != 0 )
        printf( "thread create failed." );
    
    if( pthread_join( thrd_prod , NULL ) != 0 )
        printf( " wait thread failed.");
    if( pthread_join( thrd_cons , NULL ) != 0 )
        printf( " wait thread failed.");
   
    printf("Main ready to exit !\n");

    sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
    return 0;
}

void *producer( void *arg){
    int i = 50;

	while(i>0){
        i--;
        sem_wait(&empty);
        insert_item((buffer_item)rand()%100); 
        sem_post(&full);
    }
    printf("Producer ready to exit !\n");
}
void *consumer( void *arg ){
     int i = 50;
     buffer_item item;

	 while(i>0){
        i--;
        sem_wait(&full);
        int* item0=(int*)malloc(sizeof(int));
        remove_item(&item);
        sem_post(&empty);
    }

    printf("Consumer ready to exit !\n");
}

