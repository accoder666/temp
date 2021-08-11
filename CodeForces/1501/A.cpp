#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 110;
int a[maxn], b[maxn];
int tm[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int ans;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d %d", a + i, b + i);
        for (int i = 1; i <= n; i++) scanf("%d", tm + i);
        ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += a[i] - b[i - 1] + tm[i];
            if (i == n)
                break;
            ans += (int)ceill(((long double)b[i] - a[i]) / 2), ans = max(b[i], ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}
