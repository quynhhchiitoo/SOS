#include "MyFunction.h"

int main()
{
    League PL;
    PL.load("matches.txt");
    PL.output();

    PL.sort();
    PL.standing();
    return 0;
}