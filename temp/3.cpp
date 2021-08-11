#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxlg = 17;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
inline void init(int);
inline int query(int, int, int);
int a[maxn], b[maxn], C;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
    sort(b + 1, b + n + 1);
    C = unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + C + 1, a[i]) - b;
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &x, &y);
        G[++cnt] = { y, head[x] }, head[x] = cnt;
        G[++cnt] = { x, head[y] }, head[y] = cnt;
    }
    init(n);
    int u, v, k, last = 0;
    while (m--) {
        scanf("%d %d %d", &u, &v, &k), u ^= last;
        printf("%d\n", last = query(u, v, k));
    }
    return 0;
}

struct node {
    int l, r;
    int ls, rs;
    int siz;
};
node t[maxn << 7];
int root[maxn];
int c;

inline int clone(const int u) {
    t[++c] = t[u];
    return c;
}

int build(const int l, const int r) {
    int u = ++c;
    t[u].l = l, t[u].r = r;
    if (l == r)
        return u;
    int mid = (l + r) >> 1;
    t[u].ls = build(l, mid);
    t[u].rs = build(mid + 1, r);
    return u;
}

int modify(const int u, const int p) {
    int ret = clone(u);
    t[ret].siz++;
    if (t[ret].l == t[ret].r)
        return ret;
    if (p <= t[t[ret].ls].r)
        t[ret].ls = modify(t[ret].ls, p);
    else
        t[ret].rs = modify(t[ret].rs, p);
    return ret;
}

inline int query(const int u1, const int u2, const int u3, const int u4, const int k) {
    if (t[u1].l == t[u1].r)
        return t[u1].l;
    int tmp = t[t[u1].ls].siz + t[t[u2].ls].siz - t[t[u3].ls].siz - t[t[u4].ls].siz;
    if (tmp >= k)
        return query(t[u1].ls, t[u2].ls, t[u3].ls, t[u4].ls, k);
    return query(t[u1].rs, t[u2].rs, t[u3].rs, t[u4].rs, k - tmp);
}

int lg[maxn];
int anc[maxn][maxlg], dep[maxn];

void dfs(const int u) {
    root[u] = modify(root[anc[u][0]], a[u]);
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != anc[u][0]) {
            anc[G[i].to][0] = u;
            dep[G[i].to] = dep[u] + 1;
            dfs(G[i].to);
        }
    return;
}

inline int lca(int u, int v) {
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

inline void init(const int n) {
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    root[0] = build(1, C);
    dfs(1);
    return;
}

inline int query(const int u, const int v, const int k) {
    int l = lca(u, v);
    printf("%d %d %d\n", u, v, l);
    return b[query(root[u], root[v], root[l], root[anc[l][0]], k)];
}
