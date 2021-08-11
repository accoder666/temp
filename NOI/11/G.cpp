#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxlg = 18;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int v[maxn], w[maxn], c[maxn];
int lg[maxn];
int s[maxn], e[maxn], rev[maxn << 1];
inline void build(const int&);
inline int LCA(int, int);
int id[maxn << 1];
struct query {
    int l, r, u, t, p;
    inline bool operator<(const query& rhs) const {
        if (id[l] != id[rhs.l])
            return l < rhs.l;
        if (id[r] != id[rhs.r])
            return r < rhs.r;
        return t < rhs.t;
    }
};
query Q[maxn];
struct modify {
    int p, c;
};
modify C[maxn];
long long ans[maxn], val;
inline void update(const int&, const bool& opt = false);

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= m; i++) scanf("%d", v + i);
    for (int i = 1; i <= n; i++) scanf("%d", w + i);
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &x, &y);
        G[++cnt] = { y, head[x] }, head[x] = cnt;
        G[++cnt] = { x, head[y] }, head[y] = cnt;
    }
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    build(1);
    int type, c1 = 0, c2 = 0;
    int lca;
    for (int i = 1; i <= q; i++) {
        scanf("%d %d %d", &type, &x, &y);
        switch (type) {
            case 0:
                C[++c2] = { x, y };
                break;
            case 1:
                if (s[x] > s[y])
                    x ^= y ^= x ^= y;
                lca = LCA(x, y);
                c1++;
                Q[c1].p = c1, Q[c1].t = c2;
                if (lca == x)
                    Q[c1].l = s[x], Q[c1].r = s[y];
                else
                    Q[c1].l = e[x], Q[c1].r = s[y], Q[c1].u = lca;
                break;
            default:
                break;
        }
    }
    int len = (int)powl(n << 1, (long double)2 / 3);
    for (int i = 1; i <= n << 1; i++) id[i] = (i - 1) / len + 1;
    sort(Q + 1, Q + c1 + 1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= c1; i++) {
        while (l > Q[i].l) update(rev[--l]);
        while (r < Q[i].r) update(rev[++r]);
        while (l < Q[i].l) update(rev[l++]);
        while (r > Q[i].r) update(rev[r--]);
        while (t < Q[i].t) update(++t, true);
        while (t > Q[i].t) update(t--, true);
        if (Q[i].u)
            update(Q[i].u);
        ans[Q[i].p] = val;
        if (Q[i].u)
            update(Q[i].u);
    }
    for (int i = 1; i <= c1; i++) printf("%lld\n", ans[i]);
    return 0;
}

int t;
int anc[maxn][maxlg], dep[maxn];
inline void build(const int& u) {
    rev[s[u] = ++t] = u;
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != anc[u][0]) {
            anc[G[i].to][0] = u;
            dep[G[i].to] = dep[u] + 1;
            build(G[i].to);
        }
    rev[e[u] = ++t] = u;
    return;
}

inline int LCA(int x, int y) {
    if (dep[x] < dep[y])
        x ^= y ^= x ^= y;
    while (dep[x] != dep[y]) x = anc[x][lg[dep[x] - dep[y]]];
    if (x == y)
        return x;
    for (int i = lg[dep[x]]; i >= 0; i--)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}

int b[maxn];
inline void update(const int& p, const int& sign) {
    switch (sign) {
        case 1:
            val += (long long)v[p] * w[++b[p]];
            break;
        case -1:
            val -= (long long)v[p] * w[b[p]--];
            break;
        default:
            break;
    }
    return;
}

bool f[maxn];
inline void update(const int& u, const bool& opt) {
    if (opt)
        if (f[C[u].p])
            update(C[u].p), c[C[u].p] ^= C[u].c ^= c[C[u].p] ^= C[u].c, update(C[u].p);
        else
            c[C[u].p] ^= C[u].c ^= c[C[u].p] ^= C[u].c;
    else
        update(c[u], f[u] ? -1 : 1), f[u] ^= 1;
    return;
}
