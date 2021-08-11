#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 500010, maxlg = 20;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1], T[maxn];
int head[maxn], cnt;
int headT[maxn], cntT;
int dfn[maxn];
void build(const int&);
inline int lca(int, int, int&);
int lg[maxn];
struct cmp {
    inline bool operator()(const int& x, const int& y) const { return dfn[x] < dfn[y]; }
};
int h[maxn], s[maxn], t;
bool flag[maxn];
long long dp(const int&);

int main() {
    int n;
    scanf("%d", &n);
    int u, v, w;
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { v, head[u], w }, head[u] = cnt;
        G[++cnt] = { u, head[v], w }, head[v] = cnt;
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    build(1);
    int m;
    scanf("%d", &m);
    int k;
    int l, d;
    while (m--) {
        scanf("%d", &k);
        for (int i = 1; i <= k; i++) scanf("%d", h + i), flag[h[i]] = true;
        sort(h + 1, h + k + 1, cmp());
        s[t = 1] = 1;
        cntT = headT[1] = 0;
        for (int i = 1; i <= k; i++)
            if (h[i] != 1) {
                l = lca(h[i], s[t], d);
                if (l != s[t]) {
                    while (dfn[l] < dfn[s[t - 1]]) {
                        lca(s[t], s[t - 1], d);
                        T[++cntT] = { s[t], headT[s[t - 1]], d }, headT[s[--t]] = cntT;
                    }
                    lca(l, s[t], d);
                    if (dfn[l] != dfn[s[t - 1]])
                        T[++cntT] = { s[t], 0, d }, headT[s[t] = l] = cntT;
                    else
                        T[++cntT] = { s[t--], headT[l], d }, headT[l] = cntT;
                }
                headT[s[++t] = h[i]] = 0;
            }
        for (int i = 1; i < t; i++) {
            lca(s[i], s[i + 1], d);
            T[++cntT] = { s[i + 1], headT[s[i]], d }, headT[s[i]] = cntT;
        }
        printf("%lld\n", dp(1));
        for (int i = 1; i <= k; i++) flag[h[i]] = false;
    }
    return 0;
}

int c;
int anc[maxn][maxlg], dep[maxn];
int minv[maxn][maxlg];

void build(const int& u) {
    dfn[u] = ++c;
    for (int i = 1; i <= lg[dep[u]]; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1], minv[u][i] = min(minv[u][i - 1], minv[anc[u][i - 1]][i - 1]);
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != anc[u][0]) {
            anc[G[i].to][0] = u;
            dep[G[i].to] = dep[u] + 1;
            minv[G[i].to][0] = G[i].val;
            build(G[i].to);
        }
    return;
}

inline int lca(int u, int v, int& d) {
    d = INT_MAX;
    if (dep[u] < dep[v])
        u ^= v ^= u ^= v;
    while (dep[u] > dep[v]) d = min(d, minv[u][lg[dep[u] - dep[v]]]), u = anc[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            d = min(d, min(minv[u][i], minv[v][i])), u = anc[u][i], v = anc[v][i];
    d = min(d, min(minv[u][0], minv[v][0]));
    return anc[u][0];
}

long long dp(const int& u) {
    long long ret = 0;
    for (int i = headT[u]; i; i = T[i].nxt)
        if (flag[T[i].to])
            ret += T[i].val;
        else
            ret += min(dp(T[i].to), (long long)T[i].val);
    return ret;
}
