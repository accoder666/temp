#include <cfloat>
#include <cstdio>
#include <cstring>
using namespace std;

const long double eps = 1e-4;
const int maxn = 200010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int a[maxn], b[maxn];
void dfs1(const int&);
void dfs2(const int&);
long double tmp[maxn], *p, ans;
long double val[maxn];
int m;

int main() {
    int n;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    long double mine = LDBL_MAX;
    for (int i = 1; i <= n; i++)
        if ((long double)a[i] / b[i] < mine)
            mine = (long double)a[i] / b[i];
    if (m == 1 || m == -1) {
        printf("%.2Lf\n", mine);
        return 0;
    }
    dfs1(1);
    long double l = 0, r = maxn + 10, mid;
    while (l + eps <= r) {
        mid = (l + r) / 2;
        for (int i = 1; i <= n; i++) val[i] = a[i] - mid * b[i];
        memset(tmp, 0x7f, sizeof(tmp));
        p = tmp, ans = LDBL_MAX;
        dfs2(1);
        if (ans >= 0)
            l = mid;
        else
            r = mid;
    }
    if (l >= maxn)
        printf("-1\n");
    else
        printf("%.2Lf\n", l);
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

long double *dp[maxn], v[maxn];
void dfs2(const int& u) {
    if (u == 1)
        dp[u] = p, p += len[u] + 1;
    dp[u][0] = 0, v[u] = val[u];
    if (!son[u])
        return;
    dp[son[u]] = dp[u] + 1;
    dfs2(son[u]);
    v[u] += v[son[u]], dp[u][0] -= v[son[u]];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u]) {
            dp[G[i].to] = p, p += len[G[i].to] + 1;
            dfs2(G[i].to);
            for (int j = m - len[u] - 2; j <= len[G[i].to] && j < m - 1; j++)
                if (ans > dp[u][m - j - 2] + dp[G[i].to][j] + v[u] + v[G[i].to])
                    ans = dp[u][m - j - 2] + dp[G[i].to][j] + v[u] + v[G[i].to];
            for (int j = 0; j <= len[G[i].to] && j < m - 1; j++)
                if (dp[G[i].to][j] + v[G[i].to] + val[u] < dp[u][j + 1] + v[u])
                    dp[u][j + 1] = dp[G[i].to][j] + v[G[i].to] - v[u] + val[u];
        }
    if (m - 1 <= len[u] && dp[u][m - 1] + v[u] < ans)
        ans = dp[u][m - 1] + v[u];
    return;
}
