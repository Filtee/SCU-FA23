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
    struct msgbuf buf;
    int oldtype;

    msgid = msgget(key,IPC_CREAT |0660); //������Ϣ����,���ر�ʶ��
    if(-1 == msgid)
    {
        perror("msgid");
        exit(1);
    }

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);//�յ��źź�����ִ��ȡ���������˳�����oldtype��������ȡ������������ֵ��

	printf("Sender open queue %d.\n",msgid);
	while(1)
    {
        printf("Enter your message: ");
		memset(&buf,0,sizeof(buf));
        scanf("%s",buf.mtext);
        buf.mtype = getpid();

        ret = msgsnd(msgid,&buf,sizeof(buf.mtext),0);//����������ֱ�����ͳɹ�
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
