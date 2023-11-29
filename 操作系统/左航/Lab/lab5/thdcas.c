#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "cas.h"

pthread_t tid[2];
char str[30];//全局变量，线程共享
int bolt;

void* doSomeThing1(void *arg)
{
    unsigned long i = 0;
    char temp[30];
  
    for(i=0; i<(0xFFF);i++)
   {
    while(CAS(&bolt,0,1)==0);
	strcpy(temp,"thread1 says ");
        strcpy(str,"hahaha!");
	strcat(temp,str);
	puts(temp);
    bolt = 0;
	sleep(rand()%2);
    }
    pthread_exit(0); //结束并返回值
    return NULL;
}

void* doSomeThing2(void *arg)
{
    unsigned long i = 0;
    char temp[30];
    for(i=0; i<(0xFFF);i++)
   {
    while(CAS(&bolt,0,1)==0);
	strcpy(temp,"thread2 says ");
	strcpy(str,"wowowowowo!");
	strcat(temp,str);
	puts(temp);
    bolt = 0;
	sleep(rand()%2);
   }
        
    pthread_exit(0); //结束并返回值
    return NULL;
}

int main(void)
{
    int i = 0;  
    int err;
    int *ptr[2];
    void* (*pfunc[2])(void *)={doSomeThing1,doSomeThing2};//函数指针数组
    srand(time(NULL));
    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, pfunc[i], NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }
    pthread_join(tid[0], NULL); //等待并获取返回值
    pthread_join(tid[1], NULL); //等待并获取返回值

    printf("\n return value from first thread is [%d]\n", *ptr[0]);
    printf("\n return value from second thread is [%d]\n", *ptr[1]);
    return 0;
}
