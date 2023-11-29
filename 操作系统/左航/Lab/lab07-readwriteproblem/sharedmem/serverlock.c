#include <time.h>
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<unistd.h>
#include <pthread.h>

int main(){
 
  pthread_mutex_t * sharedLock;
  pthread_mutexattr_t ma;
  char buf[50];
  key_t key = ftok("./",0x2022); //�����������������������
  if(key <0){
    perror("ftok:");
    return 1;
  }
  //���������ڴ�
  int shmid = shmget(key,4096,IPC_CREAT | 0666); //ICP_EXCL
  if(shmid < 0){
    perror("shmget:");
    return 2;
  }
  //�����깲���ڴ�����Ǿ���Ҫ���ڹ����ڴ�
  char* mem = (char*) shmat(shmid,NULL,0);
  printf("attaches shared_memory success!\n");
  //
  sharedLock = (pthread_mutex_t *)mem;
  pthread_mutexattr_init(&ma);
  pthread_mutexattr_setpshared(&ma, PTHREAD_PROCESS_SHARED);
  pthread_mutexattr_setrobust(&ma, PTHREAD_MUTEX_ROBUST);
  pthread_mutex_init(sharedLock,&ma);


  //����ͨ�ŵ��߼���������
  const char *qstpt[4]={"Hello\n","What are you doing?\n","Bye.\n","Where are you?\n"};
  const char *anspt[4]={"Hi,client.\n","I'm answering your question.\n","Look forward to seeing you, client.\n","In a server.\n"} ;
  sleep(2);
  for(int i=0;i<10;i++)
  {
  	 
	 sleep(2);
	 pthread_mutex_lock(sharedLock);
  	
  	 for(int j=0;j<4;j++)
  	 {
  	 	if(!strcmp(qstpt[j],(char *)((pthread_mutex_t *)mem+1)))
  	 	{
  	 		printf("client sent to server:%s",(char *)((pthread_mutex_t *)mem+1));//strcpy(mem,anspt[j]);
  	 		memcpy((char *)(((pthread_mutex_t *)mem+1)), anspt[j], strlen(anspt[j])+1);
  	 		break;
		}	
	 }
  	 pthread_mutex_unlock(sharedLock);
  }
  
  
//�����Ǹý��̲�ʹ�øù����ڴ�ʱ��������Ҫȥ���ù����ڴ�Ĺ���
    shmdt(mem);
    printf("deatach shared_memory success!\n");
    shmctl(shmid,IPC_RMID,NULL); //�ͷŹ����ڴ�
    return 0;

}

