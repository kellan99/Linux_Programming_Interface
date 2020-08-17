#include "tee.h"
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    test_tee(argc, argv);
    return 0;
}