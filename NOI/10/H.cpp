#include <cstdio>
using namespace std;

const int maxn = 300010;
int build(const int&, const int&);
int modify(const int&, const int&);
int query(const int&, const int&, const int&);
int root[maxn];

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    int v;
    root[0] = build(1, c);
    for (int i = 1; i <= n; i++) scanf("%d", &v), root[i] = modify(v, root[i - 1]);
    int m;
    scanf("%d", &m);
    int l, r;
    int ans;
    while (m--) {
        scanf("%d %d", &l, &r);
        ans = query((r - l + 1) >> 1, root[l - 1], root[r]);
        if (ans)
            printf("yes %d\n", ans);
        else
            printf("no\n");
    }
    return 0;
}

struct node {
    int l, r;
    int ls, rs;
    int sum;
};
node t[maxn << 5];
int cnt;

inline int clone(const int& u) {
    t[++cnt] = t[u];
    return cnt;
}

int build(const int& l, const int& r) {
    int u = ++cnt;
    t[u].l = l, t[u].r = r;
    if (l == r)
        return u;
    int mid = (l + r) >> 1;
    t[u].ls = build(l, mid);
    t[u].rs = build(mid + 1, r);
    return u;
}

int modify(const int& p, const int& u) {
    int ret = clone(u);
    t[ret].sum++;
    if (t[u].l == t[u].r)
        return ret;
    if (p <= t[t[u].ls].r)
        t[ret].ls = modify(p, t[u].ls);
    else
        t[ret].rs = modify(p, t[u].rs);
    return ret;
}

int query(const int& k, const int& u, const int& v) {
    if (t[u].l == t[u].r)
        return t[u].l;
    if (t[t[v].ls].sum - t[t[u].ls].sum > k)
        return query(k, t[u].ls, t[v].ls);
    if (t[t[v].rs].sum - t[t[u].rs].sum > k)
        return query(k, t[u].rs, t[v].rs);
    return 0;
}
