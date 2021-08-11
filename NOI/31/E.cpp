#include <cassert>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 1010, maxm = 10010;
const double eps = 1e-6;
double a[maxm][maxn], f[maxn];

int main() {
    int n, m, s, t;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lf", f + i);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &s, &t);
        while (s <= t) a[i][s++] = 1;
        scanf("%lf", a[i] + n + 1);
    }
    double ans = 0;
    int x, y;
    double min;
    while (true) {
        x = 1;
        while (x <= n && f[x] <= eps) x++;
        if (x == n + 1)
            break;
        min = (long long)1 << 31;
        for (int i = 1; i <= m; i++)
            if (a[i][x] > eps && min > a[i][n + 1] / a[i][x])
                min = a[i][n + 1] / a[i][x], y = i;
        if (min == (long long)1 << 31)
            assert(false);
        a[y][n + 1] /= a[y][x];
        for (int i = 1; i <= n; i++)
            if (i != x)
                a[y][i] /= a[y][x];
        a[y][x] = 1 / a[y][x];
        for (int i = 1; i <= m; i++)
            if (i != y && fabs(a[i][x]) > eps) {
                a[i][n + 1] -= a[i][x] * a[y][n + 1];
                for (int j = 1; j <= n; j++)
                    if (j != x)
                        a[i][j] -= a[i][x] * a[y][j];
                a[i][x] *= -a[y][x];
            }
        ans += f[x] * a[y][n + 1];
        for (int i = 1; i <= n; i++)
            if (i != x)
                f[i] -= f[x] * a[y][i];
        f[x] *= -a[y][x];
    }
    printf("%d\n", (int)round(ans));
    return 0;
}
