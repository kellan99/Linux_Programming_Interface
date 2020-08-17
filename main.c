#include "tee.h"
#include "cp.h"
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    //test_tee(argc, argv);
    if(argc >= 3)
    {
        test_cp(argv[1], argv[2]);
    }
    else
    {
        printf("param number is not enough\n");
    }
    
    
    return 0;
}