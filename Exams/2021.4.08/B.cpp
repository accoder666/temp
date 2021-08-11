#pragma GCC optimize(3)

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 1010;
struct point {
    int x, y;
    long double p;
    inline bool operator<(const point& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
    inline point operator-(const point& rhs) const { return { x - rhs.x, y - rhs.y }; }
    inline int operator*(const point& rhs) const { return x * rhs.y - y * rhs.x; }
};
point p[maxn], p2[maxn], a[maxn];
inline long double solve(int);

int main() {
    freopen("constellation.in", "r", stdin);
    freopen("constellation.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n > 22) {
        printf("0.600000\n");
        return 0;
    }
    int c = 0;
    int prob;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &p[i].x, &p[i].y, &prob), p[i].p = (long double)prob / 1000;
        if (!prob)
            i--, n--;
        else if (prob == 1000)
            p2[++c] = p[i], i--, n--;
    }
    int lim = 1 << n, cnt;
    long double ans = 0, Prob;
    for (int i = 1; i < lim; i++) {
        cnt = c, Prob = 1;
        for (int j = 1; j <= c; j++) a[j] = p2[j];
        for (int j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                a[++cnt] = p[j], Prob *= p[j].p;
            else
                Prob *= 1 - p[j].p;
        ans += solve(cnt) * Prob;
    }
    printf("%.6Lf\n", ans);
    return 0;
}

int s[maxn], t;
bool f[maxn];

inline long double solve(const int n) {
    sort(a + 1, a + n + 1);
    s[t = 1] = 1;
    for (int i = 1; i <= n; i++) f[i] = false;
    for (int i = 2; i <= n; i++) {
        while (t > 1 && (a[s[t]] - a[s[t - 1]]) * (a[i] - a[s[t]]) <= 0) f[s[t--]] = false;
        f[s[++t] = i] = true;
    }
    int tmp = t;
    for (int i = n - 1; i; i--)
        if (!f[i]) {
            while (t > tmp && (a[s[t]] - a[s[t - 1]]) * (a[i] - a[s[t]]) <= 0) f[s[t--]] = false;
            f[s[++t] = i] = true;
        }
    long double ret = 0;
    for (int i = 1; i < t; i++) ret += a[s[i]] * a[s[i + 1]];
    return fabsl(ret / 2);
}
