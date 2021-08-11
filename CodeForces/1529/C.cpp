#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
long long l[maxn], r[maxn];
inline long long dfs(int, int, bool);
long long dp[maxn][2];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int u, v;
    long long ans;
    while (t--) {
        scanf("%d", &n);
        cnt = 0;
        for (int i = 1; i <= n; i++) head[i] = 0, dp[i][0] = dp[i][1] = 0;
        for (int i = 1; i <= n; i++) scanf("%lld %lld", l + i, r + i);
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &u, &v);
            G[++cnt] = { v, head[u] }, head[u] = cnt;
            G[++cnt] = { u, head[v] }, head[v] = cnt;
        }
        ans = dfs(1, 0, false);
        printf("%lld\n", ans);
    }
    return 0;
}

inline long long dfs(const int u, const int fa, const bool f) {
    if (dp[u][f])
        return dp[u][f];
    long long ret1, ret2;
    if (!fa)
        ret1 = ret2 = 0;
    else {
        ret1 = abs((f ? l[fa] : r[fa]) - l[u]);
        ret2 = abs((f ? l[fa] : r[fa]) - r[u]);
    }
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa)
            ret1 += dfs(G[i].to, u, true), ret2 += dfs(G[i].to, u, false);
    return dp[u][f] = max(ret1, ret2);
}
