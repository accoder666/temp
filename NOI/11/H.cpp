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
long long ans[maxn], sum;
inline void update(const int&, const int&);

int main() {
    int n, m;
    scanf("%d %d %*d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    for (int i = 1; i <= m; i++) scanf("%d %d", &Q[i].l, &Q[i].r), Q[i].p = i;
    int len = (int)(n / sqrtl((long double)m));
    int p = 1;
    for (int i = 1; p <= n; i++)
        for (int j = 1; p <= n && j <= len; j++, p++) id[p] = i;
    sort(Q + 1, Q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l > Q[i].l) update(--l, 1);
        while (r < Q[i].r) update(++r, 1);
        while (l < Q[i].l) update(l++, -1);
        while (r > Q[i].r) update(r--, -1);
        ans[Q[i].p] = sum;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}

int b[maxn];
inline void update(const int& p, const int& s) {
    if (s == 1)
        sum += (b[c[p]]++) << 1 | 1;
    else
        sum -= (--b[c[p]]) << 1 | 1;
    return;
}
