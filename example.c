#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"

queue_struct_typedef queue;

int main(void)
{
        unsigned char tx_buf[10] = {0};
        unsigned char rx_buf[10] = {0};

        int ret = 0;
        int i = 0, j = 0;

        printf("Queue test!\n");

        ret = queue_init(&queue, 125);
        if (ret < 0) {
                printf("queue init error!\n");
                goto error;
        }
        
        for(i = 0; i < 3; i++) {
                printf("Queue in:");
                for(j = 0; j < 10; j++) {
                        tx_buf[j] = j * (i+1);
                        printf("%d ", tx_buf[j]);
                }
                printf("\n");
                ret = queue_in(&queue, tx_buf, sizeof(tx_buf)/sizeof(tx_buf[0]));
                if (ret < 0) {
                        printf("queue in error!\n");
                        //goto error;
                        break;
                }
        }

        for(i = 0; i < 3; i++) {
                ret = queue_out(&queue, rx_buf, 10);
                if (ret < 0) {
                        printf("queue out error!\n");
                        //goto error;
                        break;
                }
                printf("queue out:\n");
                for(int i=0; i<ret; i++)
                        printf("%d ", rx_buf[i]);
                printf("\n");
        }

        queue_deinit(&queue);

error:
        return 0;
}

