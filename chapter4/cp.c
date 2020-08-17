#include "cp.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

void test_cp(char *scr_file, char *newfile)
{
    int scr_fd, new_fd;
    scr_fd = open(scr_file, O_RDONLY);
    if(scr_fd == -1)
    {
        char buf[128];
        sprintf(buf, "open file %s failed, errno:%d", scr_file, errno);
        write(STDOUT_FILENO, buf, strlen(buf));
        return;
    }

    if(access(newfile, F_OK) == 0)
    {
        new_fd = open(newfile, O_RDWR | O_TRUNC);
    }
    else
    {
        new_fd = open(newfile, O_RDWR | O_CREAT);
    }
    
    if(new_fd == -1)
    {
        char buf[128];
        sprintf(buf, "open file %s failed, errno:%d", newfile, errno);
        write(STDOUT_FILENO, buf, strlen(buf));
        return;
    }
    
    char bufio[128];
    bool runcopy = true;
    int readlen;
    while(runcopy)
    {
        readlen = read(scr_fd, bufio, sizeof(bufio));
        if(readlen > 0)
        {
            write(new_fd, bufio, readlen);
        }
        else
        {
            runcopy = false;
        }
    }

    close(scr_fd);
    close(new_fd);
}