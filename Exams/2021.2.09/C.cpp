#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000010, sigma_size = 26;
struct node {
    int len, link;
    int nxt[sigma_size];
};
node t[maxn << 1];
int cnt, last;
int siz[maxn << 1];
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn << 1], Gcnt;
long long dfs(const int&);

int main() {
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
    t[0].len = 0, t[0].link = -1, last = 0;
    char ch = getchar();
    while (!islower(ch)) ch = getchar();
    int cur, u, v, c;
    while (islower(ch)) {
        t[cur = ++cnt].len = t[last].len + 1;
        siz[cur] = 1;
        u = last;
        while (u != -1 && !t[u].nxt[ch - 'a']) t[u].nxt[ch - 'a'] = cur, u = t[u].link;
        if (u == -1)
            t[cur].link = 0;
        else {
            v = t[u].nxt[ch - 'a'];
            if (t[u].len + 1 == t[v].len)
                t[cur].link = v;
            else {
                c = ++cnt;
                t[c].len = t[u].len + 1;
                t[c].link = t[v].link;
                memcpy(t[c].nxt, t[v].nxt, sizeof(t[c].nxt));
                while (u != -1 && t[u].nxt[ch - 'a'] == v) t[u].nxt[ch - 'a'] = c, u = t[u].link;
                t[v].link = t[cur].link = c;
            }
        }
        last = cur;
        ch = getchar();
    }
    for (int i = 1; i <= cnt; i++) G[++Gcnt] = { i, head[t[i].link] }, head[t[i].link] = Gcnt;
    printf("%lld\n", dfs(0));
    return 0;
}

long long dfs(const int& u) {
    long long ret = 0, tmp;
    for (int i = head[u]; i; i = G[i].nxt) {
        if ((tmp = dfs(G[i].to)) > ret)
            ret = tmp;
        siz[u] += siz[G[i].to];
    }
    if (siz[u] != 1 && ret < (long long)siz[u] * t[u].len)
        ret = (long long)siz[u] * t[u].len;
    return ret;
}
