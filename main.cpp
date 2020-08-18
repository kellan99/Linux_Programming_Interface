#include "tee.h"
#include "cp.h"
#include "5_1.h"
#include "5_2.h"
#include "atomic_append.h"
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    //test_tee(argc, argv);
    //test_cp(argv[1], argv[2]);
    //test_largefile();
    //test_append();
    test_atomicappend();
    return 0;
}