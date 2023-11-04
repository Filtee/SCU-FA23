#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


pthread_t tid[2]={0}; //����һ�����飬��Ϊ�߳�id

struct msgbuf
{
    long mtype;     //��Ϣ����
    char mtext[100];  //��Ϣ����
};

void *receive(void *arg)
{
    struct msgbuf buf;  //����ṹ��������Ϣ������
    int ret;

    while(1)
    {
        memset(&buf,0,sizeof(buf));  //��ʼ��

        ret = msgrcv(*(int *)arg,&buf,sizeof(buf.mtext),0,0);
        sleep(1);
        if(-1 == ret)
        {
            perror("msgrcv");
            exit(1);
        }
        if(!strncmp(buf.mtext,"bye",3))
        {
            pthread_cancel(tid[1]); //ע�⣺Ҫȡ����һ������Ŷ
            break;
        }
        printf("receive :%s\n",buf.mtext);
    }
}

void *send(void *arg)
{
    struct msgbuf buf;
    int ret,oldtype;

    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);//�յ��źź�����ִ��ȡ���������˳�����oldtype��������ȡ������������ֵ��
    while(1)
    {
        memset(&buf,0,sizeof(buf));
        scanf("%s",buf.mtext);
        buf.mtype = 1;

        ret = msgsnd(*(int *)arg,&buf,sizeof(buf.mtext),0);//����������ֱ�����ͳɹ�
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

    msgid = msgget(key,IPC_CREAT |0660); //������Ϣ����,���ر�ʶ��
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    ret = pthread_create(&tid[0],NULL,receive,(void *)&msgid); //����һ���߳�id�����������߳����ԣ�ͨ��Ϊ�գ������������߳�Ҫִ�еĺ����������ģ���Ϊ���ݸ��������Ĳ���
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

    pthread_join(tid[0],NULL);//���������̣߳�ֱ��ָ�����߳���ֹ
    pthread_join(tid[1],NULL);

    msgctl(msgid,IPC_RMID,NULL);//�Ƴ���Ϣ����
    return 0;
}
