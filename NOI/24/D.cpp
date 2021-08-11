#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 300010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
vector<pair<int, int>> Q[maxn];
void dfs1(const int&);
void dfs2(const int&);
long long ans[maxn];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    int p, k;
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &p, &k);
        Q[p].emplace_back(i, k);
    }
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}

int siz[maxn], dep[maxn];
int fa[maxn], len[maxn], son[maxn];
void dfs1(const int& u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dep[G[i].to] = dep[u] + 1;
            dfs1(G[i].to);
            siz[u] += siz[G[i].to];
            if (len[G[i].to] >= len[u])
                len[u] = len[son[u] = G[i].to] + 1;
        }
    return;
}

long long tmp[maxn << 1], *p = tmp, *dp[maxn], v[maxn];
void dfs2(const int& u) {
    if (u == 1)
        dp[u] = p, p += len[u] + 1;
    if (son[u]) {
        dp[son[u]] = dp[u] + 1;
        dfs2(son[u]);
        dp[u][0] = 0;
        v[u] = v[son[u]] + siz[son[u]] - 1;
    }
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u]) {
            dp[G[i].to] = p, p += len[G[i].to] + 1;
            dfs2(G[i].to);
            v[u] += v[G[i].to] + siz[G[i].to] - 1;
            for (int j = 0; j <= len[G[i].to]; j++) dp[u][j + 1] += dp[G[i].to][j];
        }
    dp[u][0] = -v[u];
    for (pair<int, int> i : Q[u])
        ans[i.first] = dp[u][min(i.second, len[u])] + v[u] + min(i.second, dep[u]) * (long long)(siz[u] - 1);
    return;
}
