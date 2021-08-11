#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 300010, sigma_size = 26;
inline int getfail(int, const int&);
struct node {
    node(void) { memset(ch, 0, sizeof(ch)); }
    int ch[sigma_size];
    int fail, len, val;
};
node t[maxn];
int cnt, now;
char S[maxn];

int main() {
    S[0] = '#';
    scanf("%s", S + 1);
    int n = strlen(S);
    t[++cnt].len = -1;
    t[0].fail = 1;
    int u;
    for (int i = 1; i < n; i++) {
        u = getfail(now, i);
        if (!t[u].ch[S[i] - 'a']) {
            t[++cnt].len = t[u].len + 2;
            t[cnt].fail = t[getfail(t[u].fail, i)].ch[S[i] - 'a'];
            t[u].ch[S[i] - 'a'] = cnt;
        }
        t[now = t[u].ch[S[i] - 'a']].val++;
    }
    long long ans = 0;
    for (int i = cnt; i > 1; i--) {
        t[t[i].fail].val += t[i].val;
        if (ans < (long long)t[i].val * t[i].len)
            ans = (long long)t[i].val * t[i].len;
    }
    printf("%lld\n", ans);
    return 0;
}

inline int getfail(int u, const int& p) {
    while (S[p - t[u].len - 1] != S[p]) u = t[u].fail;
    return u;
}
