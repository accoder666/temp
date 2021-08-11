#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, pair<long long, pair<string, string>>> M;
string cmd, x, s, a, b;

int main() {
    int t;
    cin >> t;
    int n;
    int p;
    long long las;
    pair<long long, pair<string, string>> u;
    while (t--) {
        cin >> n;
        cin.get();
        M.clear();
        while (n--) {
            getline(cin, cmd);
            p = 0, u.first = 0;
            x.clear();
            for (; cmd[p] != ' '; p++) x.push_back(cmd[p]);
            if (cmd[++p] == ':') {
                s.clear();
                p += 3;
                for (; p < cmd.size(); p++) s.push_back(cmd[p]);
                if (s.size() >= 3) {
                    for (int i = 0; i + 3 < s.size(); i++)
                        if (s.substr(i, 4) == "haha")
                            u.first++;
                    u.second = make_pair(s.substr(0, 3), s.substr(s.size() - 3, 3));
                } else
                    u.second = make_pair(s, "-");
            } else {
                a.clear(), b.clear();
                p += 2;
                for (; cmd[p] != ' '; p++) a.push_back(cmd[p]);
                p += 3;
                for (; p < cmd.size(); p++) b.push_back(cmd[p]);
                if (M[a].second.second == "-" && M[b].second.second == "-") {
                    s = M[a].second.first + M[b].second.first;
                    if (s.size() >= 3) {
                        for (int i = 0; i + 3 < s.size(); i++)
                            if (s.substr(i, 4) == "haha")
                                u.first++;
                        u.second = make_pair(s.substr(0, 3), s.substr(s.size() - 3, 3));
                    } else
                        u.second = make_pair(s, "-");
                } else if (M[a].second.second == "-") {
                    s = M[a].second.first + M[b].second.first;
                    u.first = M[b].first;
                    for (int i = 0; i + 3 < s.size(); i++)
                        if (s.substr(i, 4) == "haha")
                            u.first++;
                    u.second = make_pair(s.substr(0, 3), M[b].second.second);
                } else if (M[b].second.second == "-") {
                    s = M[a].second.second + M[b].second.first;
                    u.first = M[a].first;
                    for (int i = 0; i + 3 < s.size(); i++)
                        if (s.substr(i, 4) == "haha")
                            u.first++;
                    u.second = make_pair(M[a].second.first, s.substr(s.size() - 3, 3));
                } else {
                    s = M[a].second.second + M[b].second.first;
                    u.first = M[a].first + M[b].first;
                    for (int i = 0; i + 3 < s.size(); i++)
                        if (s.substr(i, 4) == "haha")
                            u.first++;
                    u.second = make_pair(M[a].second.first, M[b].second.second);
                }
            }
            M[x] = u, las = M[x].first;
        }
        cout << las << endl;
    }
    return 0;
}
