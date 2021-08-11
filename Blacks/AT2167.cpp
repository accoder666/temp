#include <cstdio>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
bool dfs(const int&);
int siz, c[3];
int vis[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    while (m--) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a], 1 }, head[a] = cnt;
        G[++cnt] = { a, head[b], -1 }, head[b] = cnt;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            siz = 0, c[0] = c[1] = c[2] = 0;
            if (!dfs(i))
                ans += (long long)(c[0] + c[1] + c[2]) * (c[0] + c[1] + c[2]);
            else if (!c[0] || !c[1] || !c[2])
                ans += siz;
            else
                ans += (long long)c[0] * c[1] + (long long)c[0] * c[2] + (long long)c[1] * c[2];
        }
    printf("%lld\n", ans);
    return 0;
}

int col[maxn];
bool dfs(const int& u) {
    bool ret = true;
    c[col[u]]++, vis[u] = true;
    for (int i = head[u]; i; i = G[i].nxt) {
        if (G[i].val == 1)
            siz++;
        if (!vis[G[i].to])
            col[G[i].to] = (col[u] + G[i].val + 3) % 3, ret &= dfs(G[i].to);
        else
            ret &= (col[G[i].to] == (col[u] + G[i].val + 3) % 3);
    }
    return ret;
}
