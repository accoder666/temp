#include <cstdio>
#include <map>
#include <stack>
#include <vector>
using namespace std;

const int maxn = 300010;
struct node {
    node(void) {
        l = r = 0;
        Q.clear();
    }
    int l, r;
    vector<int> Q;
};
node t[maxn << 2];
int x[maxn], y[maxn];
void build(const int&, const int&, const int&);
void modify(const int&, const int&, const int&, const int&);
void dfs(const int&, bool);
map<pair<int, int>, int> M;
int mx, my;

int main() {
    int q;
    scanf("%d", &q);
    build(1, q, 1);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", x + i, y + i);
        if (!M.count(make_pair(x[i], y[i]))) {
            mx = max(mx, x[i]), my = max(my, y[i]);
            M[make_pair(x[i], y[i])] = i;
        } else {
            modify(M[make_pair(x[i], y[i])], i - 1, 1, i);
            M.erase(M.find(make_pair(x[i], y[i])));
        }
    }
    for (auto it : M) modify(it.second, q, 1, it.second);
    dfs(1, false);
    printf("\n");
    return 0;
}

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

void modify(const int& l, const int& r, const int& u, const int& p) {
    if (l <= t[u].l && t[u].r <= r) {
        t[u].Q.push_back(p);
        return;
    }
    if (l <= t[ls(u)].r)
        modify(l, r, ls(u), p);
    if (t[rs(u)].l <= r)
        modify(l, r, rs(u), p);
    return;
}

int fa[maxn << 1], lc[maxn << 1], rc[maxn << 1];
stack<pair<int, pair<int, int>>> S;
long long ans = 0;

inline void reset(void) {
    for (int i = 1; i <= mx + my; i++) fa[i] = i, (i <= mx ? lc[i] : rc[i]) = 1;
    return;
}

inline int find(const int& u) {
    int ret = u;
    while (fa[ret] != ret) ret = fa[ret];
    return ret;
}

inline void merge(int u, int v) {
    if (u != v) {
        if (lc[u] + rc[u] > lc[v] + rc[v])
            u ^= v ^= u ^= v;
        S.push(make_pair(u, make_pair(lc[u], rc[u])));
        ans -= (long long)lc[u] * rc[u] + (long long)lc[v] * rc[v];
        fa[u] = v, lc[v] += lc[u], rc[v] += rc[u];
        ans += (long long)lc[v] * rc[v];
    }
    return;
}

void dfs(const int& u, bool flag) {
    if (u == 1)
        reset();
    int top = S.size();
    for (int i : t[u].Q) merge(find(x[i]), find(y[i] + mx));
    if (t[u].l == t[u].r)
        printf("%lld ", ans);
    else
        dfs(ls(u), flag), dfs(rs(u), flag);
    while (S.size() != top) {
        ans -= (long long)lc[fa[S.top().first]] * rc[fa[S.top().first]];
        lc[fa[S.top().first]] -= S.top().second.first;
        rc[fa[S.top().first]] -= S.top().second.second;
        ans += (long long)lc[S.top().first] * rc[S.top().first] +
               (long long)lc[fa[S.top().first]] * rc[fa[S.top().first]];
        fa[S.top().first] = S.top().first;
        S.pop();
    }
    return;
}
