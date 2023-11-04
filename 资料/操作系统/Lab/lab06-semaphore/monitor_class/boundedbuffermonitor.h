#ifndef BOUNDEDBUFFERMONITOR_H//条件编译指令，防止反复包含
#define  BOUNDEDBUFFERMONITOR_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define BUFF_SIZE 10
class boundedbuffer{
   private:
	pthread_mutex_t lock;
	pthread_cond_t consume_cond, produce_cond;
	int g_buff[BUFF_SIZE];
	int g_write_index;
	int g_read_index;

   public:
	int deposit(void *data);
	int removedata(void *data);

	boundedbuffer();
	~boundedbuffer();
};

#endif







