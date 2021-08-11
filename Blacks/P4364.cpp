#include <algorithm>
#include <cstdio>
#include <functional>
using namespace std;

const int maxn = 500010;
void build(const int&, const int&, const int&);
void modify(const int&, const int&, const int&, const int&);
int query(const int&, const int&);
int d[maxn], cnt[maxn];
int fa[maxn], siz[maxn];
int ans[maxn];

int main() {
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", d + i);
    sort(d + 1, d + n + 1, greater<int>());
    for (int i = n - 1; i; i--)
        if (d[i] == d[i + 1])
            cnt[i] = cnt[i + 1] + 1;
        else
            cnt[i] = 0;
    for (int i = n; i; i--) siz[fa[i] = (int)(i / k)] += (++siz[i]);
    build(1, n, 1);
    int x;
    for (int i = 1; i <= n; i++) {
        if (fa[i] && fa[i] != fa[i - 1])
            modify(ans[fa[i]], n, 1, siz[fa[i]] - 1);
        x = query(siz[i], 1);
        x += cnt[x], cnt[x]++, x -= (cnt[x] - 1), ans[i] = x;
        modify(ans[i], n, 1, -siz[i]);
    }
    for (int i = 1; i <= n; i++) printf("%d ", d[ans[i]]);
    printf("\n");
    return 0;
}

struct node {
    int l, r;
    int min, val;
};
node t[maxn << 2];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

inline void pushup(const int& u) {
    t[u].min = (t[ls(u)].min < t[rs(u)].min ? t[ls(u)].min : t[rs(u)].min);
    return;
}

inline void pushdown(const int& u) {
    t[ls(u)].min += t[u].val, t[ls(u)].val += t[u].val;
    t[rs(u)].min += t[u].val, t[rs(u)].val += t[u].val;
    t[u].val = 0;
    return;
}

void build(const int& l, const int& r, const int& u) {
    t[u].l = l, t[u].r = r, t[u].min = l;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, ls(u));
    build(mid + 1, r, rs(u));
    return;
}

void modify(const int& l, const int& r, const int& u, const int& v) {
    if (l <= t[u].l && t[u].r <= r) {
        t[u].min += v, t[u].val += v;
        return;
    }
    pushdown(u);
    if (l <= t[ls(u)].r)
        modify(l, r, ls(u), v);
    if (t[rs(u)].l <= r)
        modify(l, r, rs(u), v);
    pushup(u);
    return;
}

int query(const int& v, const int& u) {
    if (t[u].l == t[u].r)
        return t[u].l + (t[u].min < v);
    pushdown(u);
    if (v <= t[rs(u)].min)
        return query(v, ls(u));
    return query(v, rs(u));
}
