#ifndef _OPERATE_LARGE_FILES 
#define _OPERATE_LARGE_FILES 
//define __USE_LARGEFILE64 before unistd.h and fcntl.h to use open64 and lseek64
void test_largefile();
#endif