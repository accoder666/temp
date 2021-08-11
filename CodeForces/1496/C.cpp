#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010;
inline long double dist(const long long&, const long long&);
struct cmp {
    inline bool operator()(const long long& a, const long long& b) const {
        return (a > 0 ? a : -a) < (b > 0 ? b : -b);
    }
};
long long a[maxn], b[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, c1, c2;
    long long x, y;
    long double ans;
    while (t--) {
        scanf("%d", &n);
        c1 = c2 = 0;
        for (int i = 1; i <= n << 1; i++) {
            scanf("%lld %lld", &x, &y);
            if (!x)
                a[++c1] = y;
            else
                b[++c2] = x;
        }
        sort(a + 1, a + n + 1, cmp());
        sort(b + 1, b + n + 1, cmp());
        ans = 0;
        for (int i = 1; i <= n; i++) ans += dist(a[i], b[i]);
        printf("%.15Lf\n", ans);
    }
    return 0;
}

inline long double dist(const long long& x, const long long& y) {
    return sqrtl((long double)x * x + (long double)y * y);
}
