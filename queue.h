#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <pthread.h>

typedef struct queue_stuct {
        unsigned char *queue;
        int size;
        int index;
        int vaild_num;
}queue_struct_typedef;


int queue_init(queue_struct_typedef *queue_struct, int size);
int queue_deinit(queue_struct_typedef *queue_struct);
int queue_in(queue_struct_typedef *queue_struct,
                unsigned char *data,
                int len);
int queue_out(queue_struct_typedef *queue_struct,
              unsigned char *data,
              int len);
int queue_pre_out(queue_struct_typedef *queue_struct,
                  unsigned char *data,
                  int len,
                  int offset);

#endif
