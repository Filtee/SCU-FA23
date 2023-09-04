#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


pthread_t tid[2]={0}; //定义一个数组，作为线程id

struct msgbuf
{
    long mtype;     //消息类型
    char mtext[100];  //消息内容
};

void *receive(void *arg)
{
    struct msgbuf buf;  //定义结构体用作消息缓冲区
    int ret;

    while(1)
    {
        memset(&buf,0,sizeof(buf));  //初始化

        ret = msgrcv(*(int *)arg,&buf,sizeof(buf.mtext),0,0);
        sleep(1);
        if(-1 == ret)
        {
            perror("msgrcv");
            exit(1);
        }
        if(!strncmp(buf.mtext,"bye",3))
        {
            pthread_cancel(tid[1]); //注意：要取消另一个进程哦
            break;
        }
        printf("receive :%s\n",buf.mtext);
    }
}

void *send(void *arg)
{
    struct msgbuf buf;
    int ret,oldtype;

    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);//收到信号后立即执行取消动作（退出）；oldtype用来存入取消动作的类型值。
    while(1)
    {
        memset(&buf,0,sizeof(buf));
        scanf("%s",buf.mtext);
        buf.mtype = 1;

        ret = msgsnd(*(int *)arg,&buf,sizeof(buf.mtext),0);//调用阻塞，直到发送成功
        sleep(1);
        if(-1 == ret)
        {
            perror("msgsnd");
            exit(1);
        }
        if(!strncmp(buf.mtext,"bye",3))
        {
            pthread_cancel(tid[0]);
            break;
        }
    }
}


int main()
{
    int msgid,ret;
    key_t key=0;

    msgid = msgget(key,IPC_CREAT |0660); //创建消息队列,返回标识符
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    ret = pthread_create(&tid[0],NULL,receive,(void *)&msgid); //参数一：线程id；参数二：线程属性（通常为空）；参数三：线程要执行的函数；参数四：作为传递给参数三的参数
    if(0 != ret)
    {
        perror("pthread_create1");
        exit(1);
    }

    ret = pthread_create(&tid[1],NULL,send,(void *)&msgid);
    if(0 != ret)
    {
        perror("msgid");
        exit(1);
    }

    pthread_join(tid[0],NULL);//阻塞调用线程，直到指定的线程终止
    pthread_join(tid[1],NULL);

    msgctl(msgid,IPC_RMID,NULL);//移除消息队列
    return 0;
}
