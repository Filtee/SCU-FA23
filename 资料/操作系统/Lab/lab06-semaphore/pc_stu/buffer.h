#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#define BUFFER_SIZE 5
typedef int buffer_item;


int insert_item(buffer_item item);
int remove_item(buffer_item *item);

#endif // BUFFER_H_INCLUDED
