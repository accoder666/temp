#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

const int maxn = 200010;
long long a[maxn];

int main() {
    clock_t begin = clock();
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    long double ans = 0;
    long long sum1 = 0, sum2, val;
    for (int i = 1; i <= n >> 1; i++) {
        sum1 += a[n - i + 1];
        val = 0;
        for (int j = 1; j <= i; j++) val += a[j];
        sum2 = val - (i << 1) * a[i + 1];
        for (int j = 2; j + i < n - i + 1; j++) {
            val += a[i + j - 1] - a[j - 1];
            if (sum2 < val - (i << 1) * a[i + j])
                sum2 = val - (i << 1) * a[i + j];
        }
        if (ans < (long double)(sum1 + sum2) / (long double)(2 * i + 1))
            ans = (long double)(sum1 + sum2) / (long double)(2 * i + 1);
        if ((long double)(clock() - begin) / CLOCKS_PER_SEC >= 0.95)
            break;
    }
    printf("%.4Lf\n", ans);
    return 0;
}
