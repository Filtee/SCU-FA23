#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY_MSG 0x1122
#define MSGCAPACITY 10

int data[MSGCAPACITY] = {0};
struct msgbuf
{
    long mtype;     //消息类型
    int  pos;  //消息位置 
    int  content;//消息内容 
};


int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;//定义结构体用作消息缓冲区

    msgid = msgget(key,IPC_CREAT |0660); //创建消息队列,返回标识符
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    while(1)
    {
        memset(&buf,0,sizeof(buf));  //初始化
		//receive may consume message
        ret = msgrcv(msgid,&buf,2*sizeof(int),2,0);//阻塞方式 
        sleep(1);
        if(-1 == ret)
        {
            perror("may consume msgrcv error!");
            exit(1);
        }
        // now consuming...
		printf("Now consuming...data[%d]=%d\n",buf.pos,buf.content);
		data[buf.pos]=buf.content;
		//send may produce message
        buf.mtype = 1;
        buf.content =0;
        ret = msgsnd(msgid,&buf,2*sizeof(int),0);//调用阻塞，直到发送成功
    }

	if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");//移除消息队列
		exit(0);
	}
    return 0;
}
