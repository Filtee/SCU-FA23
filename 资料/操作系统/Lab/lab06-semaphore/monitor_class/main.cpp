#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "boundedbuffermonitor.h"

using namespace std;

#define PRODUCE_THREAD_SIZE 5

void *  produce(void *ptr);
void *  consume(void *ptr);

boundedbuffer bb;

int main(int argc, char * argv[]){
	pthread_t con;
	pthread_t pros[PRODUCE_THREAD_SIZE];

	srand((unsigned)time(NULL));


	pthread_create(&con, NULL, consume, NULL);//一个消费者
	usleep(1);
	int thread_args[PRODUCE_THREAD_SIZE];
	for(int i = 0; i < PRODUCE_THREAD_SIZE; i++){//多个生产者
		thread_args[i] = i + 1;
		pthread_create(&pros[i], NULL, produce, (thread_args + i));
	}

	pthread_join(con,0);
	for(int i = 0; i < PRODUCE_THREAD_SIZE; i++)
		pthread_join(pros[i],0);


	return 0;
}


void *  produce(void *ptr){

	while(1){
		bb.deposit(ptr);
		sleep(rand()%2);
   }
   return NULL;
}

void * consume(void *ptr){

   int data;
   while(1){
		bb.removedata(&data);
		sleep(rand()%2);
   }
   return NULL;
}




