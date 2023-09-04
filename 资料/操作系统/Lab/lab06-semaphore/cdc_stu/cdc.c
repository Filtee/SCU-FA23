#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int Buf1_num=0;
int Buf2_num=0;
int Buf1[10];
int Buf2[10];
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void thread_fun1(void);
void thread_fun2(void);
void thread_fun3(void);


int main(void)
{

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	int ret;

    srand(time(NULL));
	ret=pthread_create(&thread1,NULL,(void*)thread_fun1,NULL);
	if (0!=ret)	{
		fprintf(stderr,"Create pthread_fun1 error!\n");
		exit(-1);
	}
	
	ret=pthread_create(&thread2,NULL,(void*)thread_fun2,NULL);
	if (0!=ret)	{
		fprintf(stderr,"Create pthread_fun1 error!\n");
		exit(-1);
	}
	
	ret=pthread_create(&thread3,NULL,(void*)thread_fun3,NULL);
	if (0!=ret)	{
		fprintf(stderr,"Create pthread_fun3 error!\n");
		exit(-1);
	}

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);

	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);

	return 0;
}


void thread_fun1(void)
{
	char ch;
	FILE *in1 =fopen("1.dat","r");
	if(in1==NULL)
	{
		printf("Failed to open file!");
		exit (0);
	}
	while(ch != EOF)//!feof(in1))
	{
		ch=fgetc(in1);
		if(ch>= '1' && ch<='9')
		{
		
			Buf1[Buf1_num]=(int)(ch-'0');
			printf("Working on 1.dat...Buf1[%d]:%d\n",Buf1_num,Buf1[Buf1_num]);
			Buf1_num++;
		
		}

	}
	fclose(in1);
}

void thread_fun2(void)
{
	char ch;
	FILE *in2=fopen("2.dat","r");
	if(in2==NULL)
	{
		printf("Failed to open file!");
        exit (0);
	}
	while(ch != EOF)
	{
		ch=fgetc(in2);
		if(ch>='1' && ch<='9')
		{
			Buf2[Buf2_num]=(int)(ch-'0');
			printf("Working on 2.dat...Buf2[%d]:%d\n",Buf2_num,Buf2[Buf2_num]);
			Buf2_num++;
		}
	}
	fclose(in2);
}

void thread_fun3(void)
{
	int i=0;
	while(i <9)
	{


		printf("Working on thread3...\n");
		if(   )
		{
			printf("i=%d: %d+%d=%d,%d*%d=%d\n",i,Buf1[i],Buf2[i],Buf2[i]+Buf1[i],Buf1[i],Buf2[i],Buf1[i]*Buf2[i]);
			i++;
		}

	}
}


