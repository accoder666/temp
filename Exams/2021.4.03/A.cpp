#include <cstdio>
using namespace std;

const int maxn = 1000010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
void dfs1(const int&);
void dfs2(const int&);
long long ans;
int n;

int main() {
    freopen("zh.in", "r", stdin);
    freopen("zh.out", "w", stdout);
    scanf("%d", &n);
    int a, b;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a] }, head[a] = cnt;
        G[++cnt] = { a, head[b] }, head[b] = cnt;
    }
    dfs1(1);
    dfs2(1);
    printf("%lld\n", ans);
    return 0;
}

int fa[maxn], len[maxn], son[maxn];
void dfs1(const int& u) {
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dfs1(G[i].to);
            if (len[G[i].to] >= len[u])
                len[u] = len[son[u] = G[i].to] + 1;
        }
    return;
}

long long *f[maxn], *g[maxn];
long long tmp[maxn << 2], *p = tmp;
void dfs2(const int& u) {
    if (u == 1) {
        f[u] = p, p += (len[u] + 1) << 1;
        g[u] = p, p += (len[u] + 1) << 1;
    }
    f[u][0] = 1;
    if (!son[u])
        return;
    f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1;
    dfs2(son[u]);
    ans += g[u][0];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u]) {
            f[G[i].to] = p, p += (len[G[i].to] + 1) << 1;
            g[G[i].to] = p, p += (len[G[i].to] + 1) << 1;
            dfs2(G[i].to);
            for (int j = 0; j <= len[G[i].to]; j++) {
                if (j)
                    ans += f[u][j - 1] * g[G[i].to][j];
                ans += f[G[i].to][j] * g[u][j + 1];
            }
            for (int j = 0; j <= len[G[i].to]; j++) {
                g[u][j + 1] += f[u][j + 1] * f[G[i].to][j];
                if (j)
                    g[u][j - 1] += g[G[i].to][j];
                f[u][j + 1] += f[G[i].to][j];
            }
        }
    return;
}
