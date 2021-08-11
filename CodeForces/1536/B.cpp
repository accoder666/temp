#include <cstdio>
#include <set>
#include <string>
using namespace std;

const int maxn = 1010;
inline string nxt(string);
set<string> M;
char s[maxn];
string tmp;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool flag;
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        flag = false;
        for (int l = 1;; l++) {
            M.clear();
            for (int i = 1; i <= n - l + 1; i++) {
                tmp.clear();
                for (int j = i; j <= i + l - 1; j++) tmp.push_back(s[j]);
                if (!M.count(tmp))
                    M.insert(tmp);
            }
            tmp = string(l, 'a');
            for (const auto& i : M) {
                if (i != tmp) {
                    flag = true;
                    break;
                }
                tmp = nxt(i);
            }
            if (flag || tmp.length() != l + 1) {
                printf("%s\n", tmp.c_str());
                break;
            }
        }
    }
    return 0;
}

inline string nxt(string str) {
    int l = str.length(), p = -1;
    for (int i = l - 1; i >= 0; i--)
        if (str[i] != 'z') {
            p = i;
            break;
        } else
            str[i] = 'a';
    if (p == -1)
        return string(l + 1, 'a');
    str[p]++;
    return str;
}
