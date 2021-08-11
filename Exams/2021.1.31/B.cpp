#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const long long mod = 1000000007;
const int maxn = 100010, maxp = 1010;
struct edge {
    int to, nxt;
};
edge G[(maxn + 20) << 1];
int head[maxn], cnt;
int deg[maxn];
long long dist[maxp][maxp];
int vis[maxp];
queue<int> Q;
void dfs1(const int&);
void dfs2(const int&);
long long ans[maxn];

int main() {
    freopen("dist.in", "r", stdin);
    freopen("dist.out", "w", stdout);
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    long long inv = 1, b = n, e = mod - 2;
    while (e) {
        if (e & 1)
            inv = inv * b % mod;
        b = b * b % mod, e >>= 1;
    }
    int u, v;
    bool flag = true;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        deg[u]++, deg[v]++;
        flag &= (deg[u] <= 2) & (deg[v] <= 2);
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    if (n <= 1000) {
    label:
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= n; i++) {
            dist[i][i] = 0, vis[i] = i, Q.push(i);
            while (!Q.empty()) {
                u = Q.front(), Q.pop();
                for (int j = head[u]; j; j = G[j].nxt)
                    if (vis[G[j].to] != i) {
                        vis[G[j].to] = i;
                        dist[i][G[j].to] = dist[i][u] + 1;
                        Q.push(G[j].to);
                    }
            }
            for (int j = 1; j <= n; j++) ans[i] = (ans[i] + dist[i][j]) % mod;
            ans[i] = ans[i] * inv % mod;
        }
        while (q--) {
            scanf("%d", &u);
            printf("%lld\n", ans[u]);
        }
        return 0;
    }
    if (m == n - 1) {
        dfs1(1);
        dfs2(1);
        for (int i = 1; i <= n; i++) ans[i] = ans[i] * inv % mod;
        while (q--) {
            scanf("%d", &u);
            printf("%lld\n", ans[u]);
        }
    } else if (m == n && flag) {
        long long val = (((long long)(n >> 1) + 1) * (n >> 1) % mod - ((n & 1) ^ 1) * (n >> 1)) * inv % mod;
        while (q--) printf("%lld\n", val);
    } else if (m == n) {
    } else
        goto label;
    return 0;
}

int fa[maxn], siz[maxn], dis[maxn];

void dfs1(const int& u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dfs1(G[i].to);
            siz[u] += siz[G[i].to];
            dis[u] += dis[G[i].to] + siz[G[i].to];
        }
    return;
}

void dfs2(const int& u) {
    ans[u] = dis[u];
    int su, sv, du, dv;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            su = siz[u], sv = siz[G[i].to];
            du = dis[u], dv = dis[G[i].to];
            siz[u] -= siz[G[i].to];
            dis[u] -= dis[G[i].to] + siz[G[i].to];
            siz[G[i].to] += siz[u];
            dis[G[i].to] += dis[u] + siz[u];
            dfs2(G[i].to);
            siz[u] = su, siz[G[i].to] = sv;
            dis[u] = du, dis[G[i].to] = dv;
        }
    return;
}
