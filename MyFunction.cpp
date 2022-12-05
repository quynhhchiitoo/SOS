#include "MyFunction.h"

Match::Match() : home_team(""), away_team(""), result({0, 0}) {}
Match::~Match() {}
pair<string, string> Match::getName() { return {home_team, away_team}; }
pair<int, int> Match::Result() { return result; }
void Match::load(ifstream &fin)
{
    string tmp = "";
    int cnt = 0;
    while (1)
    {
        getline(fin, tmp);
        if (tmp == "")
            return;
        if (cnt == 0)
            home_team = tmp;
        else if (cnt == 1)
            away_team = tmp;
        else
        {
            int goal = tmp[tmp.length() - 1] - '0';
            scores.push_back({string(tmp.begin(), tmp.end() - 2), goal});
            if (goal == 0)
                result.first++;
            else
                result.second++;
        }
        cnt++;
    }
}

League::League() : name("") {}
League::~League() {}
League::League(string name) : name(name) {}
void League::load(string file)
{
    matches.clear();
    teams.clear();
    teams_rank.clear();

    ifstream fin(file);

    string tmp = "";
    getline(fin, tmp);
    name = tmp;

    while (!fin.eof())
    {
        getline(fin, tmp);
        if (tmp.length() == 1)
        {
            Match match;
            match.load(fin);
            matches.push_back(match);

            string ht = match.getName().first;
            string at = match.getName().second;

            if (!teams[ht])
            {
                teams_rank.push_back(ht);
                teams[ht] = teams_rank.size();
            }
            if (!teams[at])
            {
                teams_rank.push_back(at);
                teams[at] = teams_rank.size();
            }
        }
    }
    fin.close();
}

void Match::output()
{
    cout << home_team << " " << result.first
         << "-" << result.second << " " << away_team << endl;
}
void League::output()
{
    cout << "League name: " << name;
    for (int i = 0; i < matches.size(); i++)
    {
        cout << "\n"
             << i + 1 << ".\n";
        matches[i].output();
    }
}
