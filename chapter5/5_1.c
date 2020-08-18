#include "5_1.h"
#include <sys/stat.h>
#include <sys/types.h>
#define __USE_LARGEFILE64
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void test_largefile()
{
    /*************test write***************/
    int largefd = open64("largefile.txt", O_CREAT | O_RDWR | O_EXCL);
    if (largefd == -1)
    {
        write(STDOUT_FILENO, "open64 failed\n", strlen("open64 failed\n"));
        exit(-1);
    }
    else
    {
        write(STDOUT_FILENO, "open64 succeed\n", strlen("open64 succeed\n"));
    }
    
    char buf[1024 * 1024];
    int *p = (int*)buf;
    for(int i = 0; i < 1024 * 1024 /(sizeof(int)); ++i)
    {
        p[i] = i;
    }
    int len = write(largefd, buf, sizeof(buf));
    if(len <= 0)
    {
        write(STDOUT_FILENO, "write failed\n", strlen("write failed\n"));
    }
    else
    {
        write(STDOUT_FILENO, "write succeed\n", strlen("write succeed\n"));
        close(largefd);
    }
    
    /**************test read***************/
    largefd = open64("largefile.txt", O_RDONLY);
    if (largefd == -1)
    {
        write(STDOUT_FILENO, "reopen64 failed\n", strlen("reopen64 failed\n"));
        exit(-1);
    }
    else
    {
        write(STDOUT_FILENO, "reopen64 succeed\n", strlen("reopen64 succeed\n"));
    }
    int seekpos = lseek64(largefd, sizeof(int)* 20, SEEK_SET);
    char bufout[64];
    sprintf(bufout, "seekpos:%d", seekpos);
    write(STDOUT_FILENO, bufout, strlen(bufout));
    int datatoread;
    while(read(largefd, &datatoread, sizeof(datatoread)) > 0)
    {
        sprintf(bufout, "%d ", datatoread);
        //write(STDOUT_FILENO, bufout, strlen(bufout));
    }

    close(largefd);
}
