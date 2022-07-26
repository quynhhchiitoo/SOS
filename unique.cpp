#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> a = {1, 2, 3, 3, 4, 4, 4, 5, 6, 7, 7};
    a.erase(unique(a.begin(), a.end()), a.end());
    for (int x : a)
        cout << x << " ";
}