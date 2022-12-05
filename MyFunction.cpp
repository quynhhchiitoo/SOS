#include "MyFunction.h"

Team::Team()
{
    name = "";
    MP = W = D = L = GF = GA = GD = Pts = 0;
}
void Team::output()
{
    cout << name << "\t\t"
         << "\t" << MP << "\t" << W << "\t" << D << "\t" << L << "\t" << GF << "\t" << GA << "\t" << GD << "\t" << Pts << endl;
}
Team::~Team()
{
}

Match::Match() : home_team(Team()), away_team(Team()), result({0, 0}) {}
Match::~Match() {}
pair<string, string> Match::getName() { return {home_team.name, away_team.name}; }
pair<int, int> Match::Result() { return result; }
void Match::load(ifstream &fin)
{
    string tmp = "";
    int cnt = 0;
    while (1)
    {
        getline(fin, tmp);
        if (tmp == "")
            break;
        if (cnt == 0)
            home_team.name = tmp;
        else if (cnt == 1)
            away_team.name = tmp;
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

    if (result.first > result.second) // home team win
    {
        home_team.MP++;
        home_team.GF += result.first;
        home_team.W++;
        home_team.GA += result.second;
        home_team.GD = home_team.GF - home_team.GA;
        home_team.Pts += 3;

        away_team.MP++;
        away_team.GF += result.second;
        away_team.L--;
        away_team.GA += result.first;
        away_team.GD = away_team.GF - away_team.GA;
    }
    else if (result.first == result.second) // home team win
    {
        home_team.MP++;
        away_team.MP++;
        home_team.D++;
        away_team.D++;

        home_team.GF += result.first;
        home_team.GA += result.second;
        away_team.GF += result.second;
        away_team.GA += result.first;

        home_team.Pts += 1;
        away_team.Pts += 1;
    }
    else if (result.first < result.second) // home team win
    {
        away_team.MP++;
        away_team.GF += result.second;
        away_team.W++;
        away_team.GA += result.first;
        away_team.GD = away_team.GF - away_team.GA;
        away_team.Pts += 3;

        home_team.MP++;
        home_team.GF += result.first;
        home_team.L--;
        home_team.GA += result.second;
        home_team.GD = home_team.GF - home_team.GA;
    }
    return;
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

            Team home, away;
            home.name = ht;
            away.name = at;

            if (!teams[ht])
            {
                teams_rank.push_back(home);
                teams[ht] = teams_rank.size();
            }
            if (!teams[at])
            {
                teams_rank.push_back(away);
                teams[at] = teams_rank.size();
            }
        }
    }
    fin.close();
}

void Match::output()
{
    cout << home_team.name << " " << result.first
         << "-" << result.second << " " << away_team.name << endl;
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

void League::standing()
{
    cout << "\nLeague Standing\n";
    cout << "League name: " << name << endl;
    cout << "Club\t\t MP\t W\t D\t L\t GF\t GA\t GD\t Pts\n";
    for (int i = 0; i < teams_rank.size(); i++)
    {
        cout << "\n"
             << i + 1 << ".\n";
        teams_rank[i].output();
    }
}
