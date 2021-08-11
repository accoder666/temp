#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 20010;
int build(const int&, const int&);
int modify(const int&, const int&);
inline bool check(const int&);
pair<int, int> P[maxn];
int root[maxn];
int q[4];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &P[i].first), P[i].second = i;
    sort(P + 1, P + n + 1);
    root[1] = build(1, n);
    for (int i = 1; i < n; i++) root[i + 1] = modify(P[i].second, root[i]);
    int Q;
    scanf("%d", &Q);
    int x = 0;
    int l, r, mid, ans;
    while (Q--) {
        for (int& i : q) scanf("%d", &i), i = (i + x) % n + 1;
        sort(q, q + 4);
        l = 1, r = n;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid))
                l = mid + 1, ans = P[mid].first;
            else
                r = mid - 1;
        }
        printf("%d\n", x = ans);
    }
    return 0;
}

struct value {
    int maxl, maxr, sum;
    value() { maxl = maxr = INT_MIN >> 1, sum = 0; }
    inline value operator+(const value& rhs) const {
        value ret;
        ret.maxl = max(maxl, sum + rhs.maxl);
        ret.maxr = max(rhs.maxr, rhs.sum + maxr);
        ret.sum = sum + rhs.sum;
        return ret;
    }
    inline value operator+=(const value& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

struct node {
    int l, r;
    int ls, rs;
    value val;
};
node t[maxn << 5];
int cnt;

inline int clone(const int& u) {
    t[++cnt] = t[u];
    return cnt;
}

inline void pushup(const int& u) {
    t[u].val = t[t[u].ls].val + t[t[u].rs].val;
    return;
}

int build(const int& l, const int& r) {
    int u = ++cnt;
    t[u].l = l, t[u].r = r;
    t[u].val.maxl = t[u].val.maxr = t[u].val.sum = r - l + 1;
    if (l == r)
        return u;
    int mid = (l + r) >> 1;
    t[u].ls = build(l, mid);
    t[u].rs = build(mid + 1, r);
    return u;
}

int modify(const int& p, const int& u) {
    int ret = clone(u);
    if (t[ret].l == t[ret].r) {
        t[ret].val.maxl = t[ret].val.maxr = t[ret].val.sum = -1;
        return ret;
    }
    if (p <= t[t[u].ls].r)
        t[ret].ls = modify(p, t[u].ls);
    else
        t[ret].rs = modify(p, t[u].rs);
    pushup(ret);
    return ret;
}

value query(const int& l, const int& r, const int& u) {
    if (l <= t[u].l && t[u].r <= r)
        return t[u].val;
    value ret;
    if (l <= t[t[u].ls].r)
        ret += query(l, r, t[u].ls);
    if (t[t[u].rs].l <= r)
        ret += query(l, r, t[u].rs);
    return ret;
}

inline bool check(const int& p) {
    int val = 0;
    if (q[1] + 1 <= q[2] - 1)
        val += query(q[1] + 1, q[2] - 1, root[p]).sum;
    val += query(q[0], q[1], root[p]).maxr + query(q[2], q[3], root[p]).maxl;
    return val >= 0;
}
