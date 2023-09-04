#include <stdio.h>
#include <unistd.h">
#include "buffer.h"



buffer_item buffer[BUFFER_SIZE];
int in=0,out=0; 


int insert_item(buffer_item item) {    
    buffer[in] = item;
    printf("producer produced buffer[%d]:%d\n",in,buffer[in]);
    in = (in + 1) % BUFFER_SIZE;
    sleep(1);//if need disorder situation, open it
    return 0;

}


int remove_item(buffer_item *item) {
    printf("consumer consumed buffer[%d]:%d\n",out,buffer[out]);
    *item=buffer[out];
    buffer[out] = -1;
    out = (out + 1) % BUFFER_SIZE;
    return 0;

}
