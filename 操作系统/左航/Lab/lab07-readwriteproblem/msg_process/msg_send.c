#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define KEY_MSG 0x1122

struct msgbuf
{
    long mtype;     //消息类型
    char mtext[100];  //消息内容
};


int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;
    int oldtype;

    msgid = msgget(key,IPC_CREAT |0660); //创建消息队列,返回标识符
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);//收到信号后立即执行取消动作（退出）；oldtype用来存入取消动作的类型值。

	printf("Sender open queue %d.\n",msgid);
	while(1)
    {
        printf("Enter your message: ");
		memset(&buf,0,sizeof(buf));
        scanf("%s",buf.mtext);
        buf.mtype = getpid();

        ret = msgsnd(msgid,&buf,sizeof(buf.mtext),0);//调用阻塞，直到发送成功
        sleep(1);
        if(-1 == ret)
        {
            perror("msgsnd");
            exit(1);
        }
        if(!strncmp(buf.mtext,"over",4))
        {
            break;
        }
    }
    exit(0);

    return 0;
}
