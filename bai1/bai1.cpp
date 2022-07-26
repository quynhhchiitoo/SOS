#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MaxSize = 1e6 + 8;

int a[MaxSize];
int curMax;
vector<string> curMaxString;

void init()
{
    for (int i = 0; i < MaxSize; i++)
        a[i] = 0;
    curMax = 0;
}

int polyHash(string s, int base)
{
    int res = 0;
    for (char ch : s)
    {
        if ('A' <= ch and ch <= 'Z')
            ch = tolower(ch);
        if ('a' <= ch and ch <= 'z')
            res = res * base + (ch - 'a' + 1);
        res = res % MaxSize;
    }
    return res;
}

void add(string s)
{
    int hashval = polyHash(s, 13) % MaxSize;
    a[hashval]++;
    if (a[hashval] > curMax)
    {
        curMax = a[hashval];
        curMaxString.clear();
        curMaxString.push_back(s);
    }
    else if (a[hashval] == curMax)
        curMaxString.push_back(s);
}

int main()
{
    ifstream fin("inp.txt");
    string s;

    while (!fin.eof())
    {
        fin >> s;
        add(s);
    }
    cout << "Maximum frequency: " << curMax << "\nThose words are ";
    for (int i = 0; i < curMaxString.size(); i++)
    {
        cout << curMaxString[i];
        if (i < curMaxString.size() - 1)
            cout << ", ";
        else
            cout << endl;
    }
    fin.close();
}