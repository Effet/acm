#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

struct Name {
    string fsn, lsn;
    int pts;
    int rank[8];
};

struct Team {
    string name;
    int pts;
};

bool cmp1(const Name &a, const Name &b)
{
    if (a.pts != b.pts)
        return a.pts > b.pts;
    else
    {
        for (int i = 0; i < 8; ++ i)
            if (a.rank[i] != b.rank[i])
                return a.rank[i] > b.rank[i];
        if (a.lsn != b.lsn)
            return a.lsn < b.lsn;
        else
            return a.fsn < b.fsn;
    }
}

bool cmp2(const Team &a, const Team &b)
{
    if (a.pts != b.pts)
        return a.pts > b.pts;
    return a.name < b.name;
}

int val[8] = {10, 8, 6, 5, 4, 3, 2, 1};

int main(int argc, char *argv[])
{
    int cas = 0;
    string buff;
    while (true)
    {
        ++ cas;
        
        getline(cin, buff);
        int n = buff[0] - '0';
        for (int i = 1; i < buff.size() && isdigit(buff[i]); ++ i) n = n * 10 + buff[i] - '0';
        if (n == 0) break;

        // cout << n << endl;

        vector<Name> nn;
        vector<Team> tt;
        
        for (int i = 0; i < n; ++ i)
        {
            getline(cin, buff); getline(cin, buff);
            for (int j = 0; j < 8; ++ j)
            {
                getline(cin, buff);
                string name_b = buff.substr(5, 26);
                stringstream xin(name_b);
                Name name;
                xin >> name.fsn >> name.lsn;
                // cout << fsn << " " << lsn << " ";
                Team team;
                int k = buff.size() - 1;
                while (buff[k] != '.')
                    -- k;
                team.name = buff.substr(31, k - 31);
                // cout << team << endl;

                int i;
                for (i = nn.size() - 1; i >= 0; -- i)
                    if (nn[i].fsn == name.fsn && nn[i].lsn == name.lsn)
                        break;
                if (i == -1)
                {
                    i = nn.size();
                    nn.push_back(name);
                    nn[i].pts = 0;
                    for (int j = 0; j < 8; ++ j)
                        nn[i].rank[j] = 0;
                }
                nn[i].pts += val[j];
                nn[i].rank[j] ++;

                for (i = tt.size() - 1; i >= 0; -- i)
                    if (tt[i].name == team.name)
                        break;
                if (i == -1)
                {
                    i = tt.size();
                    tt.push_back(team);
                    tt[i].pts = 0;
                }
                tt[i].pts += val[j];
            }
            getline(cin, buff);
        }

        sort(nn.begin(), nn.end(), cmp1);
        sort(tt.begin(), tt.end(), cmp2);

        cout << "Season " << cas << ":" << endl;

        cout << "Drivers Standing:" << endl;
        for (int i = 0; i < nn.size(); ++ i)
        {
            buff = nn[i].fsn + " " + nn[i].lsn;
            for (int j = buff.size(); j < 26; ++ j)
                buff += " ";
            cout << buff << nn[i].pts << endl;
        }

        cout << endl;

        cout << "Teams Standing:" << endl;
        for (int i = 0; i < tt.size(); ++ i)
        {
            buff = tt[i].name;
            for (int j = buff.size(); j < 26; ++ j)
                buff += " ";
            cout << buff << tt[i].pts << endl;
        }

        cout << endl;
    }
    return 0;
}
