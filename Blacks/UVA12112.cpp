
// Problem : UVA12112 Iceman
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/UVA12112
// Memory Limit : 0 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <string>
using namespace std;
char clear_l[200], clear_r[200];
char link_l[200], link_r[200];
bool expand(string, char);
map<string, string> sol;
int n, m, caseno, target;
queue<string> q;
bool icy[200];

int main() {
    memset(icy, false, sizeof(icy));
    memset(link_l, 0, sizeof(link_l));
    memset(link_r, 0, sizeof(link_r));
    memset(clear_l, 0, sizeof(clear_l));
    memset(clear_r, 0, sizeof(clear_r));
    icy['O'] = icy['['] = icy[']'] = icy['='] = true;
    link_l['O'] = ']', link_l['['] = '=';
    link_r['O'] = '[', link_r[']'] = '=';
    clear_l['O'] = 'O', clear_l['['] = '[', clear_l[']'] = 'O', clear_l['='] = '[';
    clear_r['O'] = 'O', clear_r['['] = 'O', clear_r[']'] = ']', clear_r['='] = ']';
    while (scanf("%d %d", &n, &m) == 2 && n) {
        char map[20][20];
        for (int i = 0; i < n; i++) {
            scanf("%s", map[i]);
        }
        string s = "";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == '#') {
                    target = i * m + j;
                    map[i][j] = '.';
                }
                s += map[i][j];
            }
        }
        q.push(s);
        sol.clear();
        sol[s] = "";
        printf("Case %d: ", ++caseno);
        while (!q.empty()) {
            string str = q.front();
            q.pop();
            if (expand(str, '<'))
                break;
            if (expand(str, '>'))
                break;
            if (expand(str, 'L'))
                break;
            if (expand(str, 'R'))
                break;
        }
        while (!q.empty()) q.pop();
    }
    return 0;
}

bool expand(string str, char ch) {
    string seq = sol[str] + ch;
    int x = str.find('@');
    str[x] = '.';
    if (ch == '<' || ch == '>') {
        str[x] = '@';
        int p = (ch == '<' ? x + m - 1 : x + m + 1);
        if (str[p] == 'X')
            return false;
        else if (str[p] == '.') {
            str[p] = 'O';
            if (icy[str[p - 1]])
                str[p - 1] = link_r[str[p - 1]];
            if (str[p - 1] != '.')
                str[p] = link_l[str[p]];
            if (icy[str[p + 1]])
                str[p + 1] = link_l[str[p + 1]];
            if (str[p + 1] != '.')
                str[p] = link_r[str[p]];
        } else {
            str[p] = '.';
            if (icy[str[p - 1]])
                str[p - 1] = clear_r[str[p - 1]];
            if (icy[str[p + 1]])
                str[p + 1] = clear_l[str[p + 1]];
        }
    } else {
        int p = (ch == 'L' ? x - 1 : x + 1);
        if (str[p] == '.')
            str[p] = '@';
        else {
            if (str[p] == 'O') {
                int k;
                if (ch == 'L' && str[p - 1] == '.') {
                    for (k = p - 1; k > 0; k--) {
                        if (str[k - 1] != '.' || str[k + m] == '.') {
                            break;
                        }
                    }
                    str[p] = '.';
                    str[k] = 'O';
                    str[x] = '@';
                }
                if (ch == 'R' && str[p + 1] == '.') {
                    for (k = p + 1; k < n * m; k++) {
                        if (str[k + 1] != '.' || str[k + m] == '.') {
                            break;
                        }
                    }
                    str[p] = '.';
                    str[k] = 'O';
                    str[x] = '@';
                }
            }
            if (str[p] != '.') {
                if (str[p - m] == '.' && str[x - m] == '.') {
                    str[p - m] = '@';
                } else {
                    str[x] = '@';
                }
            }
        }
    }
    int k, r, p;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            char c = str[i * m + j];
            if (c == 'O' || c == '@') {
                for (k = i + 1; k < n; k++) {
                    if (str[k * m + j] != '.')
                        break;
                }
                str[i * m + j] = '.', str[(k - 1) * m + j] = c;
            } else if (c == '[') {
                for (r = j + 1; r < m; r++) {
                    if (str[i * m + r] == 'X' || str[i * m + r] == ']') {
                        break;
                    }
                }
                if (str[i * m + r] == ']') {
                    for (k = i + 1; k < n; k++) {
                        bool f = false;
                        for (p = j; p <= r; p++) {
                            if (str[k * m + p] != '.') {
                                f = true;
                                break;
                            }
                        }
                        if (f)
                            break;
                    }
                    for (p = j; p <= r; p++) str[i * m + p] = '.';
                    for (p = j + 1; p < r; p++) str[(k - 1) * m + p] = '=';
                    str[(k - 1) * m + j] = '[', str[(k - 1) * m + r] = ']';
                }
                j = r;
            }
        }
    }
    int h = 0, a, b, xx = str.find('@');
    a = abs(xx % m - target % m);
    if (xx / m > target / m)
        b = xx / m - target / m;
    else
        b = (xx / m < target / m ? 1 : 0);
    h = (a > b ? a : b);
    if (h + seq.length() > 15) {
        return false;
    }
    if (str.find('@') == target) {
        printf("%s\n", seq.c_str());
        return true;
    }
    if (!sol.count(str)) {
        sol[str] = seq;
        q.push(str);
    }
    return false;
}
