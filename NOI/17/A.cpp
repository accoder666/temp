#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1010;
const long double eps = 1e-4;
long double mid;
struct node {
    int a, b;
    long double v;
    inline bool operator<(const node& rhs) const { return v > rhs.v; }
};
node t[maxn];

int main() {
    int n, k;
    long double l, r, sum;
    while (scanf("%d %d", &n, &k) && (n || k)) {
        for (int i = 1; i <= n; i++) scanf("%d", &t[i].a);
        for (int i = 1; i <= n; i++) scanf("%d", &t[i].b);
        l = 0, r = 1;
        while (l + eps < r) {
            mid = (l + r) / 2.0;
            for (int i = 1; i <= n; i++) t[i].v = t[i].a - mid * t[i].b;
            sort(t + 1, t + n + 1);
            sum = 0;
            for (int i = 1; i <= n - k; i++) sum += t[i].v;
            if (sum >= 0)
                l = mid;
            else
                r = mid;
        }
        printf("%.0Lf\n", 100 * l);
    }
    return 0;
}
