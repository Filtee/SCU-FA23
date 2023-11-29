#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY_MSG 0x1122

#define MSGCAPACITY 5

int data[MSGCAPACITY] = {0};
struct msgbuf
{
    long mtype;     //消息类型
    int  pos;  //消息在数组data中的位置 
    int  content;//消息内容 
};

int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;  //定义结构体用作消息缓冲区
    int i=0;
     
    msgid = msgget(key,IPC_CREAT |0660); //创建消息队列,返回标识符
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    printf("Receiver open queue %d.\n",msgid);
    
    //set may Produce message
    buf.mtype = 1;
    for(i=0;i<MSGCAPACITY;i++)
	{
		buf.pos = i; 
		buf.content = 0;
		msgsnd(msgid,&buf,2*sizeof(int),0);
	}
		
    
    while(1)
    {
        
        //receive may produce message 
        ret = msgrcv(msgid,&buf,2*sizeof(int),1,0);//调用阻塞，直到发送成功
        sleep(1);
        if(-1 == ret)
        {
            perror("may produce msgsnd error!");
            exit(1);
        }
        //produce now... 
        data[buf.pos] = rand()%15;
		printf("Now producing...data[%d]=%d\n",buf.pos,data[buf.pos]);
        //in = (in+1)%MSGCAPACITY;
        
        //send may consume message 
        buf.mtype = 2;
	buf.content = data[buf.pos];
        ret = msgsnd(msgid,&buf,2*sizeof(int),0);//调用阻塞，直到发送成功
        
    }

    if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");//移除消息队列
		exit(0);
	}
    return 0;
}

 
