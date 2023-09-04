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
    long mtype;     //��Ϣ����
    char mtext[100];  //��Ϣ����
};

int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;  //����ṹ��������Ϣ������

    msgid = msgget(key,IPC_CREAT |0660); //������Ϣ����,���ر�ʶ��
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    printf("Receiver open queue %d.\n",msgid);
    while(1)
    {
        memset(&buf,0,sizeof(buf));  //��ʼ��

        ret = msgrcv(msgid,&buf,sizeof(buf.mtext),0,0);
        sleep(1);
        if(-1 == ret)
        {
            perror("msgrcv");
            exit(1);
        }
        if(!strncmp(buf.mtext,"over",4))
        {  
			break;
        }
        printf("receive :%s\n",buf.mtext);
    }

    if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");//�Ƴ���Ϣ����
		exit(0);
	}
    return 0;
}
