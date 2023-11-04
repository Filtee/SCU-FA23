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

boundedbuffer::boundedbuffer()
{
	g_write_index = 0;
	g_read_index = 0;
	pthread_mutex_init(&lock, 0);
	pthread_cond_init(&consume_cond,0);
	pthread_cond_init(&produce_cond,0);

}

boundedbuffer::~boundedbuffer()
{
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&produce_cond);
	pthread_cond_destroy(&consume_cond);
}

int boundedbuffer::deposit(void *data)
{
        int tempdata = *(int*)data;
		pthread_mutex_lock(&lock);
		while((g_write_index + 1) % BUFF_SIZE == g_read_index) {
			cout<<"buffer is full, producer "<<tempdata<<" is waiting.\n";
			pthread_cond_wait(&produce_cond, &lock);
		}
		g_buff[g_write_index] = tempdata;
		cout<<"producer" <<tempdata<< "put product" << tempdata<<" in buf index:"<<g_write_index<<"\n";
		g_write_index = (g_write_index + 1) % BUFF_SIZE;
		pthread_cond_signal(&consume_cond);
		pthread_mutex_unlock(&lock);

        return 0;
}

int boundedbuffer::removedata(void *data)
{

    pthread_mutex_lock(&lock);

      while(g_read_index == g_write_index) {
			cout<<"no product. consumer is waiting..\n";
			pthread_cond_wait(&consume_cond, &lock);
		}

      *(int*)data = g_buff[g_read_index];
	  cout<<"consumer consumed "<<g_buff[g_read_index]<<"in buf index "<< g_read_index<<"\n";
	  g_buff[g_read_index] = -1;
	  g_read_index = (g_read_index + 1) % BUFF_SIZE;
      pthread_cond_signal(&produce_cond);
      pthread_mutex_unlock(&lock);

      return 0;
}








