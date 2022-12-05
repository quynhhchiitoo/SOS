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
Team Team::operator+(const Team &team)
{
    Team res;
    res.name = name;
    res.MP = MP + team.MP;
    res.W = W + team.W;
    res.D = D + team.D;
    res.L = L + team.L;
    res.GF = GF + team.GF;
    res.GA = GA + team.GA;
    res.GD = GD + team.GD;
    res.Pts = MP + team.Pts;
    return res;
}

bool Team::operator>(const Team &team)
{
    if (Pts > team.Pts)
        return true;
    if (GD > team.GD)
        return true;
    if (GF > team.GF)
        return true;
    return name < team.name;
}
Team::~Team() {}
bool Team::compare(const Team &team) { return name == team.name; }

Match::Match() : home_team(Team()), away_team(Team()), result({0, 0}) {}
Match::~Match() {}
pair<string, string> Match::getName() { return {home_team.name, away_team.name}; }
pair<Team, Team> Match::getTeam() { return {home_team, away_team}; }
pair<int, int> Match::Result() { return result; }
void Match::load(ifstream &fin)
{
    fflush(stdin);
    string tmp = "";
    int cnt = 0;
    while (1)
    {
        getline(fin, tmp);
        if (tmp == "")
            break;
        if (cnt == 0)
        {
            home_team.name = tmp;
            // cout << tmp << " " << tmp.length() << endl;
        }
        else if (cnt == 1)
        {
            away_team.name = tmp;
            // cout << tmp << " " << tmp.length() << endl;
        }
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
        home_team.GA -= result.second;
        home_team.GD = home_team.GF - home_team.GA;
        home_team.Pts += 3;

        away_team.MP++;
        away_team.GF += result.second;
        away_team.L++;
        away_team.GA -= result.first;
        away_team.GD = away_team.GF - away_team.GA;
    }
    else if (result.first == result.second) // home team win
    {
        home_team.MP++;
        away_team.MP++;
        home_team.D++;
        away_team.D++;

        home_team.GF += result.first;
        home_team.GA -= result.second;
        away_team.GF += result.second;
        away_team.GA -= result.first;

        home_team.Pts += 1;
        away_team.Pts += 1;
    }
    else if (result.first < result.second) // home team win
    {
        away_team.MP++;
        away_team.GF += result.second;
        away_team.W++;
        away_team.GA -= result.first;
        away_team.GD = away_team.GF - away_team.GA;
        away_team.Pts += 3;

        home_team.MP++;
        home_team.GF += result.first;
        home_team.L++;
        home_team.GA -= result.second;
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
            home = match.getTeam().first;
            away = match.getTeam().second;

            if (!teams[ht])
            {
                teams_rank.push_back(home);
                teams[ht] = teams_rank.size();
            }
            else
            {
                for (int i = 0; i < teams_rank.size(); i++)
                    if (teams_rank[i].compare(home))
                    {
                        teams_rank[i] = teams_rank[i] + home;
                        break;
                    }
            }

            if (!teams[at])
            {
                teams_rank.push_back(away);
                teams[at] = teams_rank.size();
            }
            else
            {
                for (int i = 0; i < teams_rank.size(); i++)
                    if (teams_rank[i].compare(away))
                    {
                        teams_rank[i] = teams_rank[i] + away;
                        break;
                    }
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

void League::sort()
{
    for (int i = 0; i < teams_rank.size(); i++)
    {
        for (int j = i + 1; j < teams_rank.size(); j++)
        {
            if (teams_rank[i] > teams_rank[j])
            {
                Team temp = teams_rank[j];
                teams_rank[j] = teams_rank[i];
                teams_rank[i] = temp;
            }
        }
    }
    return;
}
