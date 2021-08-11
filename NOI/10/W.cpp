#include <cstdio>
using namespace std;

const int maxn = 100010, maxlg = 16;
inline void init(int);
inline void query(int, int, int&, int&);
int p[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", p + i);
    init(n);
    int m;
    scanf("%d", &m);
    int x, y, a, b;
    while (m--) {
        scanf("%d %d", &x, &y);
        query(x, y, a, b);
        printf("%d %d\n", a, b);
    }
    return 0;
}

int lg[maxn << 1];

int st[2][maxn][maxlg];

inline void st_init(const int n) {
    for (int i = 1; i <= n; i++) st[0][i][0] = st[1][i][0] = p[i];
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[0][j][i] =
                (st[0][j][i - 1] < st[0][j + (1 << (i - 1))][i - 1] ? st[0][j][i - 1]
                                                                    : st[0][j + (1 << (i - 1))][i - 1]),
            st[1][j][i] =
                (st[1][j][i - 1] > st[1][j + (1 << (i - 1))][i - 1] ? st[1][j][i - 1]
                                                                    : st[1][j + (1 << (i - 1))][i - 1]);
    return;
}

inline int st_query(const int t, const int l, const int r) {
    int L = lg[r - l + 1];
    return (t ^ (st[t][l][L] < st[t][r - (1 << L) + 1][L])) ? st[t][l][L] : st[t][r - (1 << L) + 1][L];
}

struct seg_node {
    int l, r;
    int val, tag;
};
seg_node t[maxn << 2];

inline int ls(const int u) { return u << 1; }

inline int rs(const int u) { return u << 1 | 1; }

inline void pushup(const int u) {
    t[u].val = (t[ls(u)].val < t[rs(u)].val ? t[ls(u)].val : t[rs(u)].val);
    return;
}

inline void pushdown(const int u) {
    if (!t[u].tag)
        return;
    t[ls(u)].val += t[u].tag, t[ls(u)].tag += t[u].tag;
    t[rs(u)].val += t[u].tag, t[rs(u)].tag += t[u].tag;
    t[u].tag = 0;
    return;
}

void seg_build(const int l, const int r, const int u) {
    t[u].l = l, t[u].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    seg_build(l, mid, ls(u));
    seg_build(mid + 1, r, rs(u));
    return;
}

void seg_modify(const int l, const int r, const int u, const int val) {
    if (t[u].r < l || r < t[u].l)
        return;
    if (l <= t[u].l && t[u].r <= r) {
        t[u].val += val, t[u].tag += val;
        return;
    }
    pushdown(u);
    seg_modify(l, r, ls(u), val);
    seg_modify(l, r, rs(u), val);
    pushup(u);
    return;
}

int seg_query(const int u = 1) {
    if (t[u].l == t[u].r)
        return t[u].l;
    pushdown(u);
    if (!t[ls(u)].val)
        return seg_query(ls(u));
    return seg_query(rs(u));
}

struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn << 1], cnt;

int anc[maxn << 1][maxlg + 1], dep[maxn << 1];

inline void lca_dfs(const int u) {
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = G[i].nxt) {
        dep[G[i].to] = dep[u] + 1;
        anc[G[i].to][0] = u;
        lca_dfs(G[i].to);
    }
    return;
}

inline int lca_anc(int u, int k) {
    while (k) u = anc[u][lg[k]], k -= (1 << lg[k]);
    return u;
}

inline int lca(int u, int v) {
    if (dep[u] < dep[v])
        u ^= v ^= u ^= v;
    u = lca_anc(u, dep[u] - dep[v]);
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

bool flag[maxn << 1];
int id[maxn], L[maxn << 1], R[maxn << 1], M[maxn << 1];
int s[maxn << 1], top, s1[maxn], t1, s2[maxn], t2;
inline void init(const int n) {
    for (int i = 2; i <= (n << 1); i++) lg[i] = lg[i >> 1] + 1;
    st_init(n);
    seg_build(1, n, 1);
    int c = 0, l, u;
    for (int i = 1; i <= n; i++) {
        while (t1 && p[i] <= p[s1[t1]]) seg_modify(s1[t1 - 1] + 1, s1[t1], 1, p[s1[t1]]), t1--;
        while (t2 && p[i] >= p[s2[t2]]) seg_modify(s2[t2 - 1] + 1, s2[t2], 1, -p[s2[t2]]), t2--;
        seg_modify(s1[t1] + 1, i, 1, -p[i]), s1[++t1] = i;
        seg_modify(s2[t2] + 1, i, 1, p[i]), s2[++t2] = i;
        id[i] = ++c, L[c] = R[c] = i;
        l = seg_query(), u = c;
        while (top && L[s[top]] >= l)
            if (flag[s[top]] && st_query(1, M[s[top]], i) - st_query(0, M[s[top]], i) == i - M[s[top]]) {
                R[s[top]] = i, M[s[top]] = L[u];
                G[++cnt] = { u, head[s[top]] }, head[s[top]] = cnt;
                u = s[top--];
            } else if (st_query(1, L[s[top]], i) - st_query(0, L[s[top]], i) == i - L[s[top]]) {
                flag[++c] = true;
                L[c] = L[s[top]], R[c] = i, M[c] = L[u];
                G[++cnt] = { s[top--], 0 }, head[c] = cnt;
                G[++cnt] = { u, head[c] }, head[c] = cnt;
                u = c;
            } else {
                c++, G[++cnt] = { u, 0 }, head[c] = cnt;
                do G[++cnt] = { s[top--], head[c] }, head[c] = cnt;
                while (top && st_query(1, L[s[top]], i) - st_query(0, L[s[top]], i) != i - L[s[top]]);
                L[c] = L[s[top]], R[c] = i;
                G[++cnt] = { s[top--], head[c] }, head[c] = cnt;
                u = c;
            }
        s[++top] = u;
        seg_modify(1, i, 1, -1);
    }
    lca_dfs(s[1]);
    return;
}

inline void query(const int x, const int y, int& a, int& b) {
    int u = id[x], v = id[y], l = lca(u, v);
    if (flag[l])
        a = L[lca_anc(u, dep[u] - dep[l] - 1)], b = R[lca_anc(v, dep[v] - dep[l] - 1)];
    else
        a = L[l], b = R[l];
    return;
}
