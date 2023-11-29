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
    long mtype;     //��Ϣ����
    int  pos;  //��Ϣ������data�е�λ�� 
    int  content;//��Ϣ���� 
};

int main()
{
    int msgid,ret;
    key_t key=KEY_MSG;
    struct msgbuf buf;  //����ṹ��������Ϣ������
    int i=0;
     
    msgid = msgget(key,IPC_CREAT |0660); //������Ϣ����,���ر�ʶ��
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
        ret = msgrcv(msgid,&buf,2*sizeof(int),1,0);//����������ֱ�����ͳɹ�
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
        ret = msgsnd(msgid,&buf,2*sizeof(int),0);//����������ֱ�����ͳɹ�
        
    }

    if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");//�Ƴ���Ϣ����
		exit(0);
	}
    return 0;
}

 
