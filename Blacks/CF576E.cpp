#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int maxn = 500010, maxk = 60;
void build(const int&, const int&, const int&);
void modify(const int&, const int&, const int&, const int&);
void dfs(const int&);
int a[maxn], b[maxn];
int e[maxn], c[maxn];
int last[maxn];
int n, k;

int main() {
    int m, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);
    for (int i = 1; i <= m; ++i) scanf("%d %d", a + i, b + i);
    for (int i = 1; i <= q; i++) scanf("%d %d", e + i, c + i);
    build(1, q, 1);
    for (int i = 1; i <= m; i++) last[i] = q + 1;
    for (int i = q; i; i--) {
        if (i != last[e[i]] - 1)
            modify(i + 1, last[e[i]] - 1, i, 1);
        last[e[i]] = i;
    }
    dfs(1);
    return 0;
}

struct node {
    int l, r;
    vector<int> V;
};
node t[maxn << 2];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

void build(const int& l, const int& r, const int& u) {
    t[u].l = l, t[u].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, ls(u));
    build(mid + 1, r, rs(u));
    return;
}

void modify(const int& l, const int& r, const int& v, const int& u) {
    if (l <= t[u].l && t[u].r <= r) {
        t[u].V.push_back(v);
        return;
    }
    if (l <= t[ls(u)].r)
        modify(l, r, v, ls(u));
    if (t[rs(u)].l <= r)
        modify(l, r, v, rs(u));
    return;
}

struct stack_node {
    int u, v, p;
};
stack<stack_node> S;
int fa[maxk][maxn << 1], siz[maxk][maxn << 1];

inline void reset(void) {
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= n; j++) fa[i][j] = j, fa[i][j + n] = j + n, siz[i][j] = siz[i][j + n] = 1;
    return;
}

inline int find(const int& p, int u) {
    while (fa[p][u] != u) u = fa[p][u];
    return u;
}

inline void merge(const int& p, int u, int v) {
    if (u == v)
        return;
    if (siz[p][u] > siz[p][v])
        u ^= v ^= u ^= v;
    S.push({ u, siz[p][u], p });
    fa[p][u] = v, siz[p][v] += siz[p][u];
    return;
}

int col[maxn];
void dfs(const int& u) {
    if (u == 1)
        reset();
    int top = S.size();
    for (int p : t[u].V)
        if (c[p]) {
            merge(c[p], find(c[p], a[e[p]]), find(c[p], b[e[p]] + n));
            merge(c[p], find(c[p], a[e[p]] + n), find(c[p], b[e[p]]));
        }
    if (t[u].l == t[u].r) {
        int p = t[u].l;
        if (find(c[p], a[e[p]]) != find(c[p], b[e[p]]))
            printf("YES\n"), col[e[p]] = c[p];
        else
            printf("NO\n"), c[p] = col[e[p]];
    } else
        dfs(ls(u)), dfs(rs(u));
    while (S.size() != top) {
        siz[S.top().p][fa[S.top().p][S.top().u]] -= S.top().v;
        fa[S.top().p][S.top().u] = S.top().u;
        S.pop();
    }
    return;
}
