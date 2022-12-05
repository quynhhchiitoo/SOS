#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

class Match
{
    string home_team, away_team;
    vector<string, bool> scores; // bool: 0 home, 1 away

public:
    void load(ifstream &fin);
};

class League
{
    string name;
    vector<Match> matches;
    unordered_map<string, int> teams;

public:
    League();
    void load(string file);
};
