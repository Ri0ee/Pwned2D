#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#include "ETime.h"

double GetTime(void)
{
    clock_t t = clock();
    return t;
}

double GetNanoTime(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_usec/(double)1000000000;
}
