#include "MyFunction.h"

int main()
{
    ListTicket list;
    list.input();
    list.sort();
    list.output("output.txt");
    list.summary();
    return 0;
}

/*
10
1
Carribean of Ocean
15
11
5
85000
1.0
80000
2
Carribean of Ocean Pacific
12
12
5
85000
1.5
40000
1
Carribean of Ocean India
17
30
5
85000
1.0
99000
2
Carribean of Ocean Vietnam
19
45
5
85000
1.5
10000
2
Carribean of Ocean Thailen
22
15
5
85000
1.5
10000
1
Carribean of Ocean Indonesia
9
10
5
85000
1.0
80000
2
Carribean of Ocean Taiwan
19
55
5
85000
1.5
40000
1
Carribean of Ocean USA
18
30
5
85000
1.0
99000
2
Carribean of Ocean England
19
10
5
85000
1.5
10000
2
Carribean of Ocean Cambodia
22
40
5
85000
1.5
10000
*/