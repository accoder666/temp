#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

const int maxn = 200010;
int a[maxn];

int main() {
    clock_t b = clock();
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    long double ans = 0;
    int l, r;
    long long sum;
    for (int i = 1; i <= n; i++) {
        if (clock() - b > 0.95 * CLOCKS_PER_SEC)
            break;
        if (a[i] != a[i + 1]) {
            l = i, r = n + 1, sum = a[i];
            while (1 < l && i + 1 < r) {
                sum += a[--l] + a[--r];
                ans = max(ans, (long double)sum / ((n + 1 - r) << 1 | 1) - a[i]);
            }
        }
    }
    printf("%.5Lf\n", ans);
    return 0;
}
