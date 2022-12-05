#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

class Match
{
    string home_team, away_team;
    vector<pair<string, bool>> scores; // bool: 0 home, 1 away
    pair<int, int> result;

public:
    Match();
    ~Match();
    pair<string, string> getName();
    void load(ifstream &fin);
    pair<int, int> Result();
    void output();
};

class League
{
    string name;
    vector<Match> matches;
    unordered_map<string, int> teams;
    vector<string> teams_rank;

public:
    League();
    League(string name);
    ~League();
    void load(string file);
    void output();
};
