#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxm = 500010, maxlg = 18;
struct kru_edge {
    int from, to, val;
    inline bool operator<(const kru_edge rhs) const { return val < rhs.val; }
};
kru_edge G[maxm];
int h[maxn];
int find(int);
int fa[maxn << 1];
struct edge {
    int to, nxt;
};
edge T[maxn << 1];
int head[maxn << 1], cnt;
int val[maxn << 1];
int lg[maxn << 1];
void dfs(int);
int anc[maxn << 1][maxlg], dep[maxn << 1];
int L[maxn << 1], R[maxn << 1];
int a[maxn], b[maxn];
int build(int, int);
int modify(int, int);
int query(int, int, int);
int root[maxn];
int n;

int main() {
    int m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", h + i);
    for (int i = 1; i <= m; i++) scanf("%d %d %d", &G[i].from, &G[i].to, &G[i].val);
    sort(G + 1, G + m + 1);
    int c = 0, fu, fv;
    for (int i = 1; i < n << 1; i++) fa[i] = i, val[i] = INT_MIN;
    for (int i = 1; i <= m && c != n - 1; i++) {
        fu = find(G[i].from), fv = find(G[i].to);
        if (fu == fv)
            continue;
        fa[fu] = fa[fv] = anc[fu][0] = anc[fv][0] = n + (++c);
        T[++cnt] = { fu, head[n + c] }, head[n + c] = cnt;
        T[++cnt] = { fv, head[n + c] }, head[n + c] = cnt;
        val[n + c] = G[i].val;
    }
    for (int i = 2; i < n << 1; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = n + 1; i <= n + c; i++)
        if (fa[i] == i)
            dfs(i);
    b[0] = -1;
    for (int i = 1; i <= n; i++) b[i] = a[i];
    sort(b + 1, b + n + 1);
    int C = unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + C + 1, a[i]) - b;
    root[0] = build(1, C);
    for (int i = 1; i <= n; i++) root[i] = modify(a[i], root[i - 1]);
    int v, x, k;
    int lastans = 0;
    while (q--) {
        scanf("%d %d %d", &v, &x, &k);
        if (lastans != -1)
            v ^= lastans, x ^= lastans, k ^= lastans;
        for (int i = lg[dep[v]]; i >= 0; i--)
            if (anc[v][i] && val[anc[v][i]] <= x)
                v = anc[v][i];
        printf("%d\n", lastans = b[query(root[L[v] - 1], root[R[v]], k)]);
    }
    return 0;
}

int find(const int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }

void dfs(const int u) {
    static int c;
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    L[u] = c + 1;
    if (u <= n) {
        a[++c] = h[u];
        R[u] = c;
        return;
    }
    for (int i = head[u]; i; i = T[i].nxt) dep[T[i].to] = dep[u] + 1, dfs(T[i].to);
    R[u] = c;
    return;
}

struct node {
    int l, r;
    int ls, rs;
    int sum;
};
node t[maxn << 5];
int C;

inline int clone(const int u) {
    t[++C] = t[u];
    return C;
}

int build(const int l, const int r) {
    int u = ++C;
    t[u].l = l, t[u].r = r;
    if (l == r)
        return u;
    int mid = (l + r) >> 1;
    t[u].ls = build(l, mid);
    t[u].rs = build(mid + 1, r);
    return u;
}

int modify(const int p, const int u) {
    if (p < t[u].l || t[u].r < p)
        return u;
    int ret = clone(u);
    t[ret].sum++;
    t[ret].ls = modify(p, t[u].ls);
    t[ret].rs = modify(p, t[u].rs);
    return ret;
}

int query(const int u, const int v, const int k) {
    if (t[v].sum - t[u].sum < k)
        return 0;
    if (t[u].l == t[u].r)
        return t[u].l;
    int c = t[t[v].rs].sum - t[t[u].rs].sum;
    if (k <= c)
        return query(t[u].rs, t[v].rs, k);
    return query(t[u].ls, t[v].ls, k - c);
}
