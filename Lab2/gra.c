#include "gra.h"

int graj(int a, int b)
{
    if (a == 1 && b == 1)
        return 0;
    if(a % 2 == 1 && b % 2 == 0)
        return 2;
    if(a == 1)
        return 2;
    else
        return 1;
}