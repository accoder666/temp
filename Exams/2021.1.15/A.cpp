#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int a[maxn], b[maxn];
struct point {
    long double x, y;
    inline bool operator<(const point& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
    inline point operator-(const point& rhs) const { return { x - rhs.x, y - rhs.y }; }
    inline long double operator*(const point& rhs) const { return x * rhs.y - y * rhs.x; }
};
point p[maxn], h[maxn];
int s[maxn], t;
bool f[maxn];

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i), b[i] = b[i - 1] + a[i];
        p[i] = { (long double)b[i], (long double)b[i] / (a[i] * 2) };
    }
    sort(p + 1, p + n + 1);
    s[++t] = 1;
    for (int i = 2; i <= n; i++) {
        while (t > 1 && (p[s[t]] - p[s[t - 1]]) * (p[i] - p[s[t]]) <= 0) f[s[t--]] = false;
        f[s[++t] = i] = true;
    }
    int tmp = t;
    for (int i = n - 1; i; i--)
        if (!f[i]) {
            while (t > tmp && (p[s[t]] - p[s[t - 1]]) * (p[i] - p[s[t]]) <= 0) f[s[t--]] = false;
            f[s[++t] = i] = true;
        }
    for (int i = 1; i <= t; i++) h[i] = p[s[i]];
    long double ans = 0;
    for (int i = 2; i < t; i++) ans += (h[i] - h[1]) * (h[i + 1] - h[1]);
    printf("%.5Lf\n", ans);
    return 0;
}
