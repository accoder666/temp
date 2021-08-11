#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long double a[maxn], b[maxn], rate[maxn];
long double c[maxn], v[maxn];
long double x[maxn], y[maxn];
long double query(const int&, const int&, const int&, const int&);
void insert(const int&, const int&, const int&, int);

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) scanf("%Lf %Lf %Lf", a + i, b + i, rate + i), c[i] = v[i] = a[i] / b[i];
    sort(c + 1, c + n + 1);
    long double ans = s;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, b[i] * query(1, n, 1, (int)(lower_bound(c + 1, c + n + 1, v[i]) - c)));
        y[i] = ans / (a[i] * rate[i] + b[i]), x[i] = y[i] * rate[i];
        insert(1, n, 1, i);
    }
    printf("%.3Lf\n", ans);
    return 0;
}

inline long double f(const int& k, const int& p) { return x[k] * c[p] + y[k]; }

int t[maxn << 2];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

long double query(const int& l, const int& r, const int& u, const int& p) {
    if (l == r)
        return f(t[u], p);
    int mid = (l + r) >> 1;
    long double ret;
    if (p <= mid)
        ret = query(l, mid, ls(u), p);
    else
        ret = query(mid + 1, r, rs(u), p);
    return max(ret, f(t[u], p));
}

void insert(const int& l, const int& r, const int& u, int p) {
    if (l == r) {
        if (f(t[u], l) > f(p, l))
            t[u] = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (f(t[u], mid) < f(p, mid))
        t[u] ^= p ^= t[u] ^= p;
    if (f(p, l) > f(t[u], l))
        insert(l, mid, ls(u), p);
    else
        insert(mid + 1, r, rs(u), p);
    return;
}
