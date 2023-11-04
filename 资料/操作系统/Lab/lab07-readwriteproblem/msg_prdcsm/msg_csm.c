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
    long mtype;     //��Ϣ����
    int  pos;  //��Ϣλ�� 
    int  content;//��Ϣ���� 
};


int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;//����ṹ��������Ϣ������

    msgid = msgget(key,IPC_CREAT |0660); //������Ϣ����,���ر�ʶ��
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    while(1)
    {
        memset(&buf,0,sizeof(buf));  //��ʼ��
		//receive may consume message
        ret = msgrcv(msgid,&buf,2*sizeof(int),2,0);//������ʽ 
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
        ret = msgsnd(msgid,&buf,2*sizeof(int),0);//����������ֱ�����ͳɹ�
    }

	if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");//�Ƴ���Ϣ����
		exit(0);
	}
    return 0;
}
