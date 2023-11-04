/* @file msort.c */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <getopt.h>
#include <time.h>

void InitData(int numofele,int numperline);


int *pbuf;//where numbers are stored
int elenum;//the number of elements to be sorted
int segcount;//the number of segment



int main(int argc, char **argv)
{
    if(argc < 3)
    {
    	printf("Please run the program with proper parameters!");
    	exit(0);
	}


	elenum = atoi(argv[1]);
	if(elenum<0 || elenum > RAND_MAX)
	{
		printf("Illegal!  The number of elements will be set to 20 by default!\n");
		elenum =20;
	}

	segcount = atoi(argv[2]);
	if(segcount <= 0 || segcount > elenum)
	{
		printf("Illegal! The number of segment will be set to (elemnet number)//3 by default!\n");
		segcount = elenum/3;
	}


	pbuf = (int *)malloc(sizeof(int)*elenum);

	InitData(elenum,segcount);

	//*********add your code here***********************

    //
    free(pbuf);
    pbuf = NULL;
	return 0;
}


// numofele:总数据条目；numperline屏幕显示时每行输出条目数 
void InitData(int numofele,int numperline)
{
	int min = RAND_MAX;
	int max = 0;
	int i,j,k;
	int temp=0;
	
	//method one
/*	while(min>max){
		printf("Please input the min value of number:  ");
		scanf("%d",&min);
		min=min>0?min:0;

		//generate a large enough range[min...max]
		max=(min+numofele*2)>RAND_MAX?RAND_MAX:min+numofele*2;
		printf("The max value of number is set to %d automatically by program!\n ",max);
	}

	srand(time(NULL));
	temp=max-min+1;
	for(i=0;i<numofele;i++)
	{
		pbuf[i] = rand()%temp + min;
		printf("%d	",pbuf[i]);
		if((i+1)%numperline == 0)
			printf("\n");
	}*/
	
	//method two
	for(i=0;i<numofele;i++)
	{
		pbuf[i] = i+1;
	}
	for(k=0;k<10000;k++)
	{
		i = rand()%numofele;
		j = rand()%numofele;
		temp=pbuf[i];
		pbuf[i]=pbuf[j];
		pbuf[j]=temp;
	}
	for(i=0;i<numofele;i++)
	{
        printf("%d	",pbuf[i]);
		if((i+1)%numperline == 0)
			printf("\n");
	}

	printf("\n\n");
}

