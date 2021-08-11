#include <cstdio>
using namespace std;

const int maxn = 150010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
void dfs(const int&);
int c[maxn], dfn[maxn];
void build(const int&, const int&, const int&);
long long query(const int&, const int&, const int&);
inline void access(int);

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v), u++, v++;
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    dfs(1);
    build(1, n, 1);
    int q;
    scanf("%d", &q);
    char opt;
    while (q--) {
        opt = getchar();
        while (opt != 'q' && opt != 'O') opt = getchar();
        scanf("%d", &u), u++;
        switch (opt) {
            case 'q':
                printf("%.10Lf\n", (long double)query(dfn[u], dfn[u] + c[u] - 1, 1) / c[u]);
                break;
            case 'O':
                access(u);
                break;
            default:
                break;
        }
    }
    return 0;
}

int fa[maxn], dep[maxn];
int clock, rev[maxn];

void dfs(const int& u) {
    c[u] = 1;
    dfn[u] = ++clock, rev[clock] = u;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dep[G[i].to] = dep[u] + 1;
            dfs(G[i].to);
            c[u] += c[G[i].to];
        }
    return;
}

struct node {
    int l, r;
    long long sum, tag;
};
node t[maxn << 2];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

inline void pushup(const int& u) {
    t[u].sum = t[ls(u)].sum + t[rs(u)].sum;
    return;
}

inline void pushdown(const int& u) {
    if (!t[u].tag)
        return;
    t[ls(u)].tag += t[u].tag, t[ls(u)].sum += t[u].tag * (t[ls(u)].r - t[ls(u)].l + 1);
    t[rs(u)].tag += t[u].tag, t[rs(u)].sum += t[u].tag * (t[rs(u)].r - t[rs(u)].l + 1);
    t[u].tag = 0;
    return;
}

void build(const int& l, const int& r, const int& u) {
    t[u].l = l, t[u].r = r;
    if (l == r) {
        t[u].sum = dep[rev[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, ls(u));
    build(mid + 1, r, rs(u));
    pushup(u);
    return;
}

void modify(const int& l, const int& r, const int& u, const int& val) {
    if (l <= t[u].l && t[u].r <= r) {
        t[u].tag += val, t[u].sum += val * (t[u].r - t[u].l + 1);
        return;
    }
    pushdown(u);
    if (l <= t[ls(u)].r)
        modify(l, r, ls(u), val);
    if (t[rs(u)].l <= r)
        modify(l, r, rs(u), val);
    pushup(u);
    return;
}

long long query(const int& l, const int& r, const int& u) {
    if (l <= t[u].l && t[u].r <= r)
        return t[u].sum;
    pushdown(u);
    long long ret = 0;
    if (l <= t[ls(u)].r)
        ret += query(l, r, ls(u));
    if (t[rs(u)].l <= r)
        ret += query(l, r, rs(u));
    return ret;
}

int son[maxn][2];

inline int get(const int& u) { return son[fa[u]][1] == u; }

inline bool isroot(const int& u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

inline void rotate(const int& u) {
    int x = fa[u], y = fa[x], k = get(u);
    fa[u] = y;
    if (!isroot(x))
        son[y][get(x)] = u;
    son[x][k] = son[u][k ^ 1];
    fa[son[u][k ^ 1]] = x;
    son[u][k ^ 1] = x;
    fa[x] = u;
    return;
}

inline void splay(const int& u) {
    for (int f; f = fa[u], !isroot(u); rotate(u))
        if (!isroot(f))
            rotate(get(u) == get(f) ? f : u);
    return;
}

inline int find(int u) {
    while (son[u][0]) u = son[u][0];
    return u;
}

inline void access(int u) {
    int v;
    for (int f = 0; u; u = fa[f = u]) {
        splay(u);
        if (son[u][1]) {
            v = find(son[u][1]);
            modify(dfn[v], dfn[v] + c[v] - 1, 1, 1);
        }
        son[u][1] = f;
        if (f) {
            v = find(f);
            modify(dfn[v], dfn[v] + c[v] - 1, 1, -1);
        }
    }
    return;
}
