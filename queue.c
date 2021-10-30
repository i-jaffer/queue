#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static pthread_mutex_t queue_mutex;

int queue_init(queue_struct_typedef *queue_struct, int size)
{
        int ret = 0;
        ret = pthread_mutex_init(&queue_mutex, NULL);
        if(ret != 0) {
                fprintf(stderr, "pthread_mutex_init error in %s\n", __FILE__);
                goto error;
        }

        pthread_mutex_lock(&queue_mutex);
        queue_struct->queue = (unsigned char *)malloc(size * sizeof(unsigned char));
        queue_struct->size = size;
        queue_struct->index = 0;
        queue_struct->vaild_num = 0;
        pthread_mutex_unlock(&queue_mutex);

        if(queue_struct->queue == NULL) {
                fprintf(stderr, "malloc error in %s", __FILE__);
                ret = -1;
                goto error;
        }

error:
        return ret;
}

int queue_deinit(queue_struct_typedef *queue_struct)
{
        int ret = 0;
        pthread_mutex_lock(&queue_mutex);
        free(queue_struct->queue);
        queue_struct->size = 0;
        queue_struct->index = 0;
        queue_struct->vaild_num = 0;
        pthread_mutex_unlock(&queue_mutex);
        pthread_mutex_destroy(&queue_mutex);

        return 0;
}

int queue_in(queue_struct_typedef *queue_struct,
                unsigned char *data,
                int len)
{
        int ret = 0;
        int i = 0;
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

        if((queue_struct->vaild_num + len) > queue_struct->size)
                len = queue_struct->size - queue_struct->vaild_num;

        pthread_mutex_lock(&queue_mutex);
        for(i=0; i<len; i++) {
                queue_struct->queue[queue_struct->index] = *(data+i);
                queue_struct->vaild_num ++;
                queue_struct->index = (++(queue_struct->index)) % (queue_struct->size);
        }
        pthread_mutex_unlock(&queue_mutex);

out:
        return ret;
}

int queue_out(queue_struct_typedef *queue_struct,
                unsigned char *data,
                int len)
{
        int ret = 0, i = 0;
        int queue_head = 0;
        if(queue_struct == NULL) {
                ret = -1;
                goto out;
        }
        if(queue_struct->queue == NULL) {
                ret = -1;
                goto out;
        }
        if(queue_struct->vaild_num ==  0) {
                ret = 0;
                goto out;
        }

        if(len > queue_struct->vaild_num)
                len = queue_struct->vaild_num;
        ret = len;

        pthread_mutex_lock(&queue_mutex);
        for(i=0; i<len; i++) {
                queue_head = (queue_struct->index + queue_struct->size
                               - queue_struct->vaild_num) % (queue_struct->size);
                *(data+i) = queue_struct->queue[queue_head];
                queue_struct->queue[queue_head] = 0;
                queue_struct->vaild_num --;
        }
        pthread_mutex_unlock(&queue_mutex);

out:
        return ret;
}

int queue_pre_out(queue_struct_typedef *queue_struct,
                  unsigned char *data,
                  int len,
                  int offset)
{
        int ret = 0, i = 0;
        int queue_head = 0;

        if((data == NULL) || (queue_struct == NULL)) {
                ret = -1;
                goto error;
        }

        if((len+offset) > queue_struct->vaild_num) {
                ret = -1;
                goto error;
        }
        pthread_mutex_lock(&queue_mutex);
        queue_head = (queue_struct->index + queue_struct->size
                      - queue_struct->vaild_num) % (queue_struct->size);
        queue_head = queue_head + offset;
        for(i = 0; i < len; i++) {
                *(data+i) = queue_struct->queue[queue_head];
                queue_head = (++queue_head) % queue_struct->size;
        }
        pthread_mutex_unlock(&queue_mutex);
        ret = len;

error:
        return ret;
}


