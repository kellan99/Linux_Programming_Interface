#include "tee.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
char *getfilename(int argc, char *argv[]);
void test_tee(int argc, char *argv[])
{
    char buf[1024];
    char *filename = getfilename(argc, argv);
    if(strcmp(filename, "") == 0)
    {
        bool runtee = true;
        while( runtee )
        {
            int len = read(STDIN_FILENO, buf, 1024);
            if(len > 0)
            {
                write(STDOUT_FILENO, buf, len);    
            }
            else if(len == 0)
            {
                runtee = false;
            }
            else
            {
                char errbuf[64];
                sprintf(errbuf, "read err no:%d", errno);
                write(STDERR_FILENO, errbuf, strlen(errbuf));
            }
            
        }
    }
    else
    {
        int filefd = -1;
        if(access(filename, F_OK) == 0)
        {
            filefd = open(filename, O_TRUNC | O_RDWR);
        }
        else
        {
            filefd = open(filename, O_RDWR | O_CREAT | O_EXCL );
        }
        if(filefd == -1)
        {
            char errbuf[64];
            sprintf(errbuf, "error is %d", errno);
            write(STDERR_FILENO, errbuf, strlen(errbuf));
            exit(0);
        }

        bool runtee = true;
        while( runtee )
        {
            int len = read(STDIN_FILENO, buf, 1024);
            if(len > 0)
            {
                write(filefd, buf, len);    
                write(STDERR_FILENO, "WRITING", strlen("WRITING"));
            }
            else if(len == 0)
            {
                runtee = false;
                write(STDERR_FILENO, "WRITE SUCCEED", strlen("WRITE SUCCEED"));
            }
            else
            {
                char errbuf[64];
                sprintf(errbuf, "read err no:%d", errno);
                write(STDERR_FILENO, errbuf, strlen(errbuf));
            }
        }

        close(filefd);
    }

}

char *getfilename(int argc, char *argv[])
{
    char file_name[128];
    char ch;
    //getopt三个特殊变量
    //optarg全局变量指向参数的选项值
    //optind指向再次调用getopt时的argv索引值
    //optopt最后一个未知选项
    //单冒号表示后边必跟参数，可以带空格或者不带空格
    //双冒号表示可带可不带参数，但是有参数必须与选项空格隔开
    while(ch = getopt(argc, argv, "f:"))
    {
        switch(ch)
        {
            case 'f':
            {
                printf("filename is: %s\n", optarg);
                return optarg;
            }
            break;
            case '?':
            {
                printf("param parser failed\n");
                return "";
            }
            break;
            default:
                printf("wrong param option: %c\n", ch);
            break;
        }
    }

    return "";
}