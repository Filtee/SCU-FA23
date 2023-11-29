#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>

int main(){
  pthread_mutex_t * sharedLock;
  //client���ɵĹ����ڴ�keyֵ���Ǻ�server���ɵ�key��һ����
  //��Ϊ����ʹ�� ftok����Ĳ���Ҳ��һ����
  key_t key = ftok("./",0x2022); 
  if(key <0){
    perror("ftok");
    return 1;
  } 
  //����Ĺ����ڴ治��Ҫ�ڴ����ˣ�ֻ��Ҫʹ��server�˴����Ĺ����ڴ漴��
  //���ǵ�key�Ǻ�server��ͬ�ģ����ԾͿ��Ա�֤clientҲ�ǿ���server�Ĺ����ڴ�
  //���ڲ���Ҫclient���������ڴ棬�������ǵ����������������IPC_CREAT
  //��ʾ���к�key��صĹ����ڴ棬��ô�ͻ᷵�ظù����ڴ���û��������ٴ���
  int shmid = shmget(key,4096,IPC_CREAT);
  if(shmid <0){
    perror("shmget:");
    return 1;
  }
  //���˹����ڴ����Ǿ���Ҫ���ڸù����ڴ浽client���̵������ַ
  char* mem = (char*)shmat(shmid,NULL,0);
  sharedLock = (pthread_mutex_t *)mem; 
  //���ڹ����ڴ浽client���̳ɹ��������client��ҵ���߼���������
//���Ǹ������ڴ�ÿ��һ�뷢����ĸ
  srand(time(NULL));
  const char *strpt[4]={"Hello\n","What are you doing?\n","Bye.\n","Where are you?\n"};
  
  for(int i=0;i<10;i++){
  	 int pos = rand()%4;
  	 pthread_mutex_lock(sharedLock);
    
        memcpy((char *)((pthread_mutex_t *)mem+1), strpt[pos], strlen(strpt[pos])+1);
    	//printf("server answers client:%s",(pthread_mutex_t *)mem)+1);
    	pthread_mutex_unlock(sharedLock);
        sleep(2);//˯������Ϊ�˹۲�server�˿��Ƿ���յ�client���͵�����
	pthread_mutex_lock(sharedLock);
	printf("server answers client:%s",(char *)((pthread_mutex_t *)mem+1));
	pthread_mutex_unlock(sharedLock);
  }
  

  //��ҵ���߼������꣬����ʹ�ù����ڴ棬���ǿ���ȥ���ù����ڴ�Ĺ���
  shmdt(mem);
  return 0;
}

