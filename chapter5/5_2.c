#include "5_2.h"
#include <sys/stat.h>
#include <sys/types.h>
#define __USE_LARGEFILE64
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void test_append()
{
    int filefd = open64("largefile.txt", O_RDWR | O_APPEND);
    if( filefd == -1)
    {
        printf("largefile.txt open failed errno %d\n", errno);
        exit(-1);
    }

    int data_to_write = 0;
    while(write(filefd, &data_to_write, sizeof(data_to_write)))
    {
        ++data_to_write;
        if(data_to_write > 20)
        {
            break;
        }
    }
    close(filefd);

    filefd = open64("largefile.txt", O_RDWR);
    if( filefd == -1)
    {
        printf("largefile.txt reopen failed\n");
        exit(-1);
    }

    printf("lseek64 %ld\n", lseek64(filefd, 1024 * 1024, SEEK_SET));
    while(read(filefd, &data_to_write, sizeof(data_to_write)))
    {
        printf(",%d",data_to_write);
    }
    close(filefd);
}