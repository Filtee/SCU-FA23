#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"


//extern

sem_t empty,full;               
pthread_mutex_t mutex;  
        
void *producer( void *arg );    
void *consumer( void *arg );    

int main(int argc , char *argv[]){
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_t thrd_prod , thrd_cons;
 
    srand(time(NULL));
    
    if( pthread_create( &thrd_prod , NULL, producer ,
                NULL ) != 0 )
        printf( "thread create failed." );

    if( pthread_create( &thrd_cons , NULL, consumer ,
                NULL ) != 0 )
        printf( "thread create failed." );

    
    if( pthread_join( thrd_prod , NULL ) != 0 )
        printf( " wait thread failed.");
    if( pthread_join( thrd_cons , NULL ) != 0 )
        printf( " wait thread failed.");
   
    printf("Main ready to exit !\n");
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *producer( void *arg){
    int i = 50;

	while(i>0){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        i--;
        insert_item((buffer_item)rand()%100); 
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand() % 2);
    }
    printf("Producer ready to exit !\n");
}
void *consumer( void *arg ){
     int i = 50;
     buffer_item item;

	 while(i>0){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        i--;
        remove_item(&item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(rand() % 2);
    }

    printf("Consumer ready to exit !\n");
}

