#include "atomic_append.h"
#include <thread>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <syscall.h>

using namespace std;

void threadappend(const char * filename)
{
    int filefd = open(filename, O_RDWR | O_APPEND);
    if(filefd == -1)
    {
        cout<<"file "<<filename <<" open failed, errno:"<<errno<<endl;
        exit(0);
    }
    int data_to_write = 0;
    while(data_to_write < 10000)
    {
        write(filefd, &data_to_write, sizeof(data_to_write));
        //cout<<lseek(filefd, 0, SEEK_CUR)<<"-";
        ++data_to_write;
    }

    close(filefd);
    cout<<"thread exit"<<endl;
}

void threadnoappend(const char * filename)
{
    int filefd = open(filename, O_RDWR);
    if(filefd == -1)
    {
        cout<<"file "<<filename <<" open failed, errno:"<<errno<<endl;
        exit(0);
    }
    int data_to_write = 0;
    int pos =0;
    while(data_to_write < 10000)
    {
        write(filefd, &data_to_write, sizeof(data_to_write));
        //cout<<lseek(filefd, 0, SEEK_CUR)<<",";
        ++data_to_write;
    }

    close(filefd);
    cout<<"thread exit"<<endl;
}


void test_atomicappend()
{
    system("touch append.txt noappend.txt");
    system("chmod +rw append.txt noappend.txt");
    system("sync");
    //a和b线程输出的lseek(fd, 0, SEEK_CUR)没有重合，保持了原子性
    thread a(&threadappend, "append.txt");
    thread b(&threadappend, "append.txt");
    a.detach();
    b.detach();

    //c和d线程输出的lseek(fd, 0, SEEK_CUR)有重合
    thread c(&threadappend, "noappend.txt");
    thread d(&threadnoappend, "noappend.txt");
    c.detach();
    d.detach();
    
    pause();
}