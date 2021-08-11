#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 50010;
int id[maxn];
struct query {
    int l, r, p;
    inline bool operator<(const query& rhs) const {
        if (id[l] != id[rhs.l])
            return l < rhs.l;
        if (id[l] & 1)
            return r < rhs.r;
        return r > rhs.r;
    }
};
query Q[maxn];
int c[maxn];
long long ans1[maxn], ans2[maxn], sum;
inline void update(const int&, const int&);
long long gcd(const long long&, const long long&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        cnt++;
        scanf("%d %d", &Q[cnt].l, &Q[cnt].r);
        if (Q[cnt].l == Q[cnt].r)
            cnt--, ans2[i] = 1;
        else
            Q[cnt].p = i;
    }
    int len = (int)(n / sqrtl((long double)cnt));
    int p = 1;
    for (int i = 1; p <= n; i++)
        for (int j = 1; p <= n && j <= len; j++, p++) id[p] = i;
    sort(Q + 1, Q + cnt + 1);
    int l = 1, r = 0;
    long long g;
    for (int i = 1; i <= cnt; i++) {
        while (l > Q[i].l) update(--l, 1);
        while (r < Q[i].r) update(++r, 1);
        while (l < Q[i].l) update(l++, -1);
        while (r > Q[i].r) update(r--, -1);
        ans1[Q[i].p] = sum, ans2[Q[i].p] = (long long)(r - l + 1) * (r - l) >> 1;
        g = gcd(ans1[Q[i].p], ans2[Q[i].p]);
        ans1[Q[i].p] /= g, ans2[Q[i].p] /= g;
    }
    for (int i = 1; i <= m; i++) printf("%lld/%lld\n", ans1[i], ans2[i]);
    return 0;
}

int b[maxn];
inline void update(const int& p, const int& s) {
    if (s == 1)
        sum += (b[c[p]]++);
    else
        sum -= (--b[c[p]]);
    return;
}

long long gcd(const long long& x, const long long& y) {
    if (!y)
        return x;
    return gcd(y, x % y);
}
