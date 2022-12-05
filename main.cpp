#include "MyFunction.h"

int main()
{
    League PL;
    PL.load("matches.txt");
    PL.output();
    return 0;
}