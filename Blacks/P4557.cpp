#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
struct point {
    int x, y;
    inline bool operator<(const point& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
    inline point operator+(const point& rhs) const { return { x + rhs.x, y + rhs.y }; }
    inline point operator-(const point& rhs) const { return { x - rhs.x, y - rhs.y }; }
    inline long long operator*(const point& rhs) const { return (long long)x * rhs.y - (long long)y * rhs.x; }
    [[nodiscard]] inline long long len(void) const { return (long long)x * x + (long long)y * y; }
};
struct cmp {
    explicit cmp(const point& p) : p(p) {}
    point p;
    inline bool operator()(const point& a, const point& b) const {
        long long v = (a - p) * (b - p);
        return v ? v > 0 : (a - p).len() < (b - p).len();
    }
};
point a[maxn], b[maxn];
point v[2][maxn], c[maxn << 1];
inline int convex(point*, const int&);

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].x, &a[i].y);
    for (int i = 1; i <= m; i++) scanf("%d %d", &b[i].x, &b[i].y), b[i].x = -b[i].x, b[i].y = -b[i].y;
    n = convex(a, n);
    m = convex(b, m);
    for (int i = 1; i < n; i++) v[0][i] = a[i + 1] - a[i];
    v[0][n] = a[1] - a[n];
    for (int i = 1; i < m; i++) v[1][i] = b[i + 1] - b[i];
    v[1][m] = b[1] - b[m];
    c[1] = a[1] + b[1];
    int cnt = 1, p1 = 1, p2 = 1;
    while (p1 <= n && p2 <= m)
        cnt++, c[cnt] = c[cnt - 1] + ((v[0][p1] * v[1][p2] >= 0) ? v[0][p1++] : v[1][p2++]);
    while (p1 <= n) cnt++, c[cnt] = c[cnt - 1] + v[0][p1++];
    while (p2 <= m) cnt++, c[cnt] = c[cnt - 1] + v[1][p2++];
    while (cnt > 1 && (c[cnt] - c[cnt - 1]) * (c[1] - c[cnt - 1]) <= 0) cnt--;
    point d;
    int x;
    while (q--) {
        scanf("%d %d", &d.x, &d.y);
        if ((d - c[1]) * (c[1] - c[cnt]) > 0 || (d - c[1]) * (c[2] - c[1]) > 0)
            printf("0\n");
        else {
            x = lower_bound(c + 2, c + cnt + 1, d, cmp(c[1])) - (c + 1);
            printf("%d\n", (d - c[x]) * (c[x % cnt + 1] - c[x]) <= 0);
        }
    }
    return 0;
}

bool f[maxn];
int s[maxn], t;
point h[maxn];
inline int convex(point* p, const int& n) {
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) f[i] = false;
    s[t = 1] = 1;
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
    t--;
    for (int i = 1; i <= t; i++) h[i] = p[s[i]];
    for (int i = 1; i <= t; i++) p[i] = h[i];
    return t;
}
