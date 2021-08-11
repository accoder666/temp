#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int build(const int&, const int&);
int modify(const int&, const int&, const int&);
long long query(const long long&, const int&, const int&);
int root[maxn];
struct juice {
    int d, p, l;
    inline bool operator<(const juice& rhs) const { return d < rhs.d; }
};
juice j[maxn];
struct node {
    int l, r;
    int ls, rs;
    long long cnt, sum;
};
node t[maxn << 5];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int lim = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &j[i].d, &j[i].p, &j[i].l);
        if (j[i].p > lim)
            lim = j[i].p;
    }
    sort(j + 1, j + n + 1);
    root[0] = build(1, lim);
    for (int i = 1; i <= n; i++) root[i] = modify(j[i].p, j[i].l, root[i - 1]);
    long long g, l;
    int L, R, mid, ans;
    while (m--) {
        scanf("%lld %lld", &g, &l);
        L = 1, R = n, ans = -1;
        while (L <= R) {
            mid = (L + R) >> 1;
            if (query(l, root[mid - 1], root[n]) <= g && t[root[n]].cnt - t[root[mid - 1]].cnt >= l)
                L = mid + 1, ans = mid;
            else
                R = mid - 1;
        }
        if (ans == -1)
            printf("-1\n");
        else
            printf("%d\n", j[ans].d);
    }
    return 0;
}

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

int modify(const int& p, const int& l, const int& u) {
    int ret = clone(u);
    t[ret].cnt += l, t[ret].sum += (long long)p * l;
    if (t[ret].l == t[ret].r)
        return ret;
    if (p <= t[t[u].ls].r)
        t[ret].ls = modify(p, l, t[u].ls);
    else
        t[ret].rs = modify(p, l, t[u].rs);
    return ret;
}

long long query(const long long& k, const int& u, const int& v) {
    if (t[u].l == t[u].r)
        return t[u].l * k;
    long long x = t[t[v].ls].cnt - t[t[u].ls].cnt;
    if (k <= x)
        return query(k, t[u].ls, t[v].ls);
    return t[t[v].ls].sum - t[t[u].ls].sum + query(k - x, t[u].rs, t[v].rs);
}
