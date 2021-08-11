#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 50010, maxlg = 16, maxm = 100010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int col[maxn];
int lg[maxn];
int s[maxn], e[maxn], rev[maxn << 1];
inline void build(const int&);
inline int LCA(int, int);
int id[maxn << 1];
struct query {
    int l, r, u, p, a, b;
    inline bool operator<(const query& rhs) const {
        if (id[l] != id[rhs.l])
            return l < rhs.l;
        return r < rhs.r;
    }
};
query Q[maxm];
int ans[maxm], val;
inline void change(const int&);
bool flag[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", col + i);
    int root;
    int u, v;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &u, &v);
        if (!u || !v)
            root = u + v;
        else {
            G[++cnt] = { v, head[u] }, head[u] = cnt;
            G[++cnt] = { u, head[v] }, head[v] = cnt;
        }
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    build(root);
    int lca;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d %d", &u, &v, &Q[i].a, &Q[i].b);
        if (s[u] > s[v])
            u ^= v ^= u ^= v;
        lca = LCA(u, v);
        Q[i].p = i;
        if (lca == u)
            Q[i].l = s[u], Q[i].r = s[v];
        else
            Q[i].l = e[u], Q[i].r = s[v], Q[i].u = lca;
    }
    int len = (int)sqrtl(n << 1);
    for (int i = 1; i <= n << 1; i++) id[i] = (i - 1) / len + 1;
    sort(Q + 1, Q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l > Q[i].l) change(rev[--l]);
        while (r < Q[i].r) change(rev[++r]);
        while (l < Q[i].l) change(rev[l++]);
        while (r > Q[i].r) change(rev[r--]);
        if (Q[i].u)
            change(Q[i].u);
        ans[Q[i].p] = val - (Q[i].a != Q[i].b && flag[Q[i].a] && flag[Q[i].b]);
        if (Q[i].u)
            change(Q[i].u);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}

int c;
int anc[maxn][maxlg], dep[maxn];
inline void build(const int& u) {
    rev[s[u] = ++c] = u;
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != anc[u][0]) {
            anc[G[i].to][0] = u;
            dep[G[i].to] = dep[u] + 1;
            build(G[i].to);
        }
    rev[e[u] = ++c] = u;
    return;
}

inline int LCA(int u, int v) {
    if (dep[u] < dep[v])
        u ^= v ^= u ^= v;
    while (dep[u] != dep[v]) u = anc[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

int b[maxn];
inline void change(const int& p, const int& sign) {
    switch (sign) {
        case 1:
            val += !(b[p]++);
            break;
        case -1:
            val -= !(--b[p]);
            break;
        default:
            break;
    }
    flag[p] = b[p];
    return;
}

bool f[maxn];
inline void change(const int& u) {
    change(col[u], f[u] ? -1 : 1), f[u] ^= 1;
    return;
}
