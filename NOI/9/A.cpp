#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt;
    long long v, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
void dfs1(const int&);
void dfs2(const int&);
void build(const int&, const int&, const int&);
void solve(const int&);
long long ans;
int L, U;

int main() {
    int n;
    scanf("%d %d %d", &n, &L, &U);
    int a, b;
    long long v;
    long long l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        scanf("%d %d %lld", &a, &b, &v), v *= 10000;
        G[++cnt] = { b, head[a], v, 0 }, head[a] = cnt;
        G[++cnt] = { a, head[b], v, 0 }, head[b] = cnt;
        if (v > r)
            r = v;
    }
    dfs1(1);
    dfs2(1);
    build(1, n, 1);
    long long mid;
    while (l < r) {
        mid = (l + r) >> 1;
        for (int i = 1; i <= cnt; i++) G[i].val = G[i].v - mid;
        ans = INT_MIN;
        solve(1);
        if (ans >= 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%.3Lf\n", (long double)l / 10000);
    return 0;
}

int fa[maxn], len[maxn], son[maxn], e[maxn];
void dfs1(const int& u) {
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dfs1(G[i].to);
            if (len[u] <= len[G[i].to])
                len[u] = len[son[u] = G[e[u] = i].to] + 1;
        }
    return;
}

int dfn[maxn], c;
void dfs2(const int& u) {
    dfn[u] = ++c;
    if (son[u])
        dfs2(son[u]);
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u])
            dfs2(G[i].to);
    return;
}

struct node {
    int l, r;
    long long val;
};
node t[maxn << 3];

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

void clear(const int& u) {
    t[u].val = INT_MIN;
    if (t[u].l == t[u].r)
        return;
    clear(ls(u));
    clear(rs(u));
    return;
}

void modify(const int& p, const long long& v, const int& u) {
    if (v > t[u].val)
        t[u].val = v;
    if (t[u].l == t[u].r)
        return;
    if (p <= t[ls(u)].r)
        modify(p, v, ls(u));
    else
        modify(p, v, rs(u));
    return;
}

long long query(const int& l, const int& r, const int& u) {
    if (l <= t[u].l && t[u].r <= r)
        return t[u].val;
    long long ret = INT_MIN, tmp;
    if (l <= t[ls(u)].r && (tmp = query(l, r, ls(u))) > ret)
        ret = tmp;
    if (t[rs(u)].l <= r && (tmp = query(l, r, rs(u))) > ret)
        ret = tmp;
    return ret;
}

inline int max(const int& x, const int& y) { return x > y ? x : y; }

inline int min(const int& x, const int& y) { return x < y ? x : y; }

long long dp[maxn << 1], v[maxn << 1];
void solve(const int& u) {
    if (u == 1)
        clear(1);
    int d = dfn[u], dv;
    dp[d] = v[d] = 0;
    if (!son[u]) {
        modify(d, 0, 1);
        return;
    }
    solve(son[u]);
    v[d] += v[d + 1] + G[e[u]].val, dp[d] = -v[d];
    modify(d, dp[d], 1);
    long long tmp;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u]) {
            solve(G[i].to);
            dv = dfn[G[i].to];
            for (int j = max(1, L - len[u]); j <= len[G[i].to] + 1; j++) {
                tmp = G[i].val + dp[dv + j - 1] + v[d] + v[dv] +
                      query(d + max(1, L - j), d + min(len[u], U - j), 1);
                if (tmp > ans)
                    ans = tmp;
            }
            for (int j = 1; j <= len[G[i].to] + 1; j++)
                if (G[i].val + dp[dv + j - 1] + v[dv] > v[d] + dp[d + j]) {
                    dp[d + j] = G[i].val + dp[dv + j - 1] + v[dv] - v[d];
                    modify(d + j, dp[d + j], 1);
                }
        }
    if (len[u] >= L) {
        tmp = v[d] + query(d + L, d + min(U, len[u]), 1);
        if (tmp > ans)
            ans = tmp;
    }
    return;
}
