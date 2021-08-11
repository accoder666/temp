#include <algorithm>
#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const int maxn = 200010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1], T[maxn];
int head[maxn], cnt;
int headT[maxn], cntT;
int a[maxn], rev[maxn];
long long phi[maxn], mu[maxn], g[maxn];
int p[maxn], pc;
bool f[maxn];
inline long long inv(long long);
int dfn[maxn];
inline void init(void);
inline int lca(int, int);
struct cmp {
    inline bool operator()(const int& x, const int& y) const { return dfn[x] < dfn[y]; }
};
int h[maxn], s[maxn], t;
long long val[maxn];
long long dfs(const int&);

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), rev[a[i]] = i;
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!f[i])
            p[++pc] = i, phi[i] = i - 1, mu[i] = -1;
        for (int j = 1; j <= pc && i * p[j] <= n; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                mu[i * p[j]] = -mu[i], phi[i * p[j]] = phi[i] * (p[j] - 1);
            else {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
        }
    }
    long long tmp;
    for (int i = 1; i <= n >> 1; i++) {
        tmp = i * inv(phi[i]) % mod;
        for (int j = 1; i * j <= n >> 1; j++) g[i * j] = g[i * j] + tmp * mu[j];
    }
    for (int i = 1; i <= n >> 1; i++) {
        g[i] %= mod;
        if (g[i] < 0)
            g[i] += mod;
    }
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &x, &y);
        G[++cnt] = { y, head[x] }, head[x] = cnt;
        G[++cnt] = { x, head[y] }, head[y] = cnt;
    }
    init();
    int k, l;
    long long ans = 0;
    for (int d = 1; d <= n >> 1; d++) {
        k = 0;
        for (int i = d; i <= n; i += d) val[h[++k] = rev[i]] = phi[i];
        sort(h + 1, h + k + 1, cmp());
        s[t = 1] = 1;
        cntT = headT[1] = 0;
        for (int i = 1; i <= k; i++)
            if (h[i] != 1) {
                l = lca(s[t], h[i]);
                if (l != s[t]) {
                    while (dfn[l] < dfn[s[t - 1]])
                        T[++cntT] = { s[t], headT[s[t - 1]] }, headT[s[--t]] = cntT;
                    if (l != s[t - 1])
                        T[++cntT] = { s[t], 0 }, headT[s[t] = l] = cntT;
                    else
                        T[++cntT] = { s[t--], headT[l] }, headT[l] = cntT;
                }
                headT[s[++t] = h[i]] = 0;
            }
        for (int i = 1; i < t; i++) T[++cntT] = { s[i + 1], headT[s[i]] }, headT[s[i]] = cntT;
        ans = (ans + (g[d] * dfs(1) << 1)) % mod;
        for (int i = 1; i <= k; i++) val[h[i]] = 0;
    }
    ans = ans * inv((long long)n * (n - 1) % mod) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}

inline long long inv(long long x) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * x % mod;
        x = x * x % mod, e >>= 1;
    }
    return ret;
}

int fa[maxn], dep[maxn], siz[maxn], son[maxn];

void dfs1(const int& u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt)
        if (fa[u] != G[i].to) {
            fa[G[i].to] = u;
            dep[G[i].to] = dep[u] + 1;
            dfs1(G[i].to);
            siz[u] += siz[G[i].to];
            if (siz[G[i].to] > siz[son[u]])
                son[u] = G[i].to;
        }
    return;
}

int top[maxn];

int c;
void dfs2(const int& u) {
    dfn[u] = ++c;
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u])
            top[G[i].to] = G[i].to, dfs2(G[i].to);
    return;
}

inline void init(void) {
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    return;
}

inline int lca(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}

long long sum[maxn], dp[maxn];
long long dfs(const int& u) {
    long long ret = 0, tmp;
    sum[u] = val[u], dp[u] = 0;
    for (int i = headT[u]; i; i = T[i].nxt) {
        tmp = dfs(T[i].to);
        ret = (ret + tmp + sum[T[i].to] * (dp[u] + sum[u] * (dep[T[i].to] - dep[u]) % mod) % mod +
               dp[T[i].to] * sum[u] % mod) %
              mod;
        sum[u] = (sum[u] + sum[T[i].to]) % mod;
        dp[u] = (dp[u] + dp[T[i].to] + sum[T[i].to] * (dep[T[i].to] - dep[u])) % mod;
    }
    return ret;
}
