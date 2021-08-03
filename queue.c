#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int queue_init(queue_struct_typedef *queue_struct, int size)
{
        pthread_mutex_lock(&(queue_struct->mutex));
        queue_struct->queue = (int *)malloc(size);
        queue_struct->size = size;
        queue_struct->index = 0;
        queue_struct->vaild_num = 0;
        pthread_mutex_unlock(&(queue_struct->mutex));

        if(queue_struct->queue == NULL)
                return -1;
        else
                return 0;
}

int queue_deinit(queue_struct_typedef *queue_struct)
{
        int ret = 0;
        pthread_mutex_lock(&(queue_struct->mutex));
        free(queue_struct->queue);
        queue_struct->size = 0;
        queue_struct->index = 0;
        queue_struct->vaild_num = 0;
        pthread_mutex_unlock(&(queue_struct->mutex));

        return 0;
}

int queue_in(queue_struct_typedef *queue_struct, int data)
{
        int ret = 0;
        if(queue_struct == NULL) {
                ret = -1;
                goto out;
        }
        if(queue_struct->queue == NULL) {
                ret = -1;
                goto out;
        }

        if(queue_struct->vaild_num == queue_struct->size) {
                ret = -1;
                goto out;
        }

        pthread_mutex_lock(&(queue_struct->mutex));
        queue_struct->queue[queue_struct->index] = data;
        queue_struct->vaild_num ++;
        queue_struct->index = (++(queue_struct->index)) % (queue_struct->size);
        pthread_mutex_unlock(&(queue_struct->mutex));

out:
        return ret;
}

int queue_out(queue_struct_typedef *queue_struct)
{
        int ret = 0;
        int vaild_index = 0;
        if(queue_struct == NULL) {
                ret = -1;
                goto out;
        }
        if(queue_struct->queue == NULL) {
                ret = -1;
                goto out;
        }

        if(queue_struct->vaild_num ==  0) {
                ret = -1;
                goto out;
        }

        pthread_mutex_lock(&(queue_struct->mutex));
        vaild_index = (queue_struct->index + queue_struct->size - queue_struct->vaild_num) % 
                (queue_struct->size);
        ret = queue_struct->queue[vaild_index];
        queue_struct->queue[vaild_index] = 0;
        queue_struct->vaild_num --;
        pthread_mutex_unlock(&(queue_struct->mutex));

out:
        return ret;
}


