#ifndef _ATOMIC_APPEND_H_
#define _ATOMIC_APPEND_H_
//两个线程同时打开文件进行写入操作
//1.两个线程同时使用O_APPEND标志打开，同时写入后文件大小等于两次写入数据总和的大小
//2.一个或者两个线程不使用O_APPEND打开文件，同时写入后文件size小于两次写入的数据总size之和
//原因：内核高速缓存管理，导致lseek计算部分重合了，猜测write和lseek交叉执行导致lseek计算的尺寸丢了
void test_atomicappend();
#endif