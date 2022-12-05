#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

class Team
{
public:
    string name;
    int MP, W, D, L, GF, GA, GD, Pts;
    Team();
    void output();
    bool compare(const Team &team);
    Team operator+(const Team &team);
    ~Team();
};
class Match
{
    Team home_team, away_team;
    vector<pair<string, bool>> scores; // bool: 0 home, 1 away
    pair<int, int> result;

public:
    Match();
    ~Match();
    pair<string, string> getName();
    void load(ifstream &fin);
    pair<int, int> Result();
    pair<Team, Team> getTeam();
    void output();
};

class League
{
    string name;
    vector<Match> matches;
    unordered_map<string, int> teams;
    vector<Team> teams_rank; // fix

public:
    League();
    League(string name);
    ~League();
    void load(string file);
    void output();
    void standing();
};
