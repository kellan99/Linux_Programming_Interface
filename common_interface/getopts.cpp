#include "getopts.h"
#include <getopt.h>
#include <iostream>
using namespace std;
//int getopt(int argc, char * const argv[],const char *optstring);
/*
    optstring为自定义选项规则，形如"a:b::cd:" 分别表示程序支持的命令行短选项有-a -b -c -d
    冒号含义如下：
        只有一个字符不带冒号，只表示选项。如 c:  -c
        只有一个字符后带冒号，表示需要带一个参数 如a或d:  -a 100 或者 -a100 ，可以空格隔开或者不隔开
        只有一个字符后带两个冒号，表示后边参数可有可无，但是带参数时，必须带空格隔开
    <getopt.h中提供几个全局变量，帮助解析>
        char *optarg —— 指向当前选项参数(如果有参数的话)的指针。ps: 当前选项由返回值传递；
        int optind —— 再次调用 getopt() 时的下一个 argv 指针的索引。
        int optopt —— 最后一个未知选项。一般当出现未知选项，或缺少参数时，它就会保存这个未知选项。
        int opterr ­—— 如果不希望getopt()打印出错信息，则只要将该全局变量opterr设为0即可。
    返回值描述：
        1.选项成功找到，返回选项字母
        2.如果遇到选项不在optstring中，返回字符'?'
        3.如果遇到丢失参数，则返回值依赖optstring第一个字符，如果为':'则返回':',否则返回'?'
        4.参数解析完毕返回 -1
*/

//int getopt_long(int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);
/*
    前三个参数与getopt函数参数含义相同；
    struct option
    {
      const char *name; //  has_arg can't be an enum because some compilers complain about type mismatches in all the code that assumes it is an int.  
      int has_arg;      //  0,1,2 #define no_argument 0 ;#define required_argument 1; #define optional_argument 2
      int *flag;        //  常为NULL
      int val;          //  flag为NULL时，val表示与短选项对应的选项值出现name时在短选项中寻找val
    };
    例如{"a123", required_argument, NULL, 'a'}，表示如果出现长参数选项--a123 100，则解析到此项时按照短参数'a'的规则解析，required_argument对应a后有一个冒号
*/

//#define OPT
#define OPT_LOG
void test_getopts(int argc, char *argv[])
{
    const char *short_optis;
#ifdef OPT
    char ch;
    while((ch = getopt(argc, argv, short_optis)) != -1)
    {
        switch(ch)
        {
            case 'a':cout<<'a';break;
            case 'b':cout<<'b';break;
            case 'c':cout<<'c';break;
            case 'd':cout<<'d';break;
            case ':':cout<<':';break;
            case '?':cout<<'?';break;
            default :cout<<ch ;break;
        }
        cout <<", param is: "<<optarg<<endl;
    } 
#endif

#ifdef OPT_LOG
    struct option long_opts[]=
    {
        {"a123", required_argument, NULL, 'a'},     //输入 --a123时按照-a解释,  不能使用-a123
        {"b456", optional_argument, NULL, 'b'},     
        {"c789", no_argument, NULL, 'c'},
        {0,0,0,0}
    };
    char ch;
    while((ch = getopt_long(argc, argv, short_optis, long_opts, NULL)) != -1)
    {
        switch(ch)
        {
            case 'a':cout<<'a';break;
            case 'b':cout<<'b';break;
            case 'c':cout<<'c';break;
            case 'd':cout<<'d';break;
            case ':':cout<<':';break;
            case '?':cout<<'?';break;
            default :cout<<ch ;break;
        }
        cout <<", param is: "<<optarg<<endl;
    }
#endif // !OPT_LOG
}