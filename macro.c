#include "macro.h"


double Random0to1()
{
    return ((double) rand() / (RAND_MAX));
}

double RandomRangeDouble(double start, double end)
{
    double length = (end - start);
    return Random0to1() * length - length/2;
}

int RandomRangeInt(int start, int end)
{
    int length = (end - start);
    int n = rand() % length;
    
    return n + start;
}