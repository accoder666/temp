#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 200010;
int a[maxn], b[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, l, r;
    long long ans;
    while (t--) {
        scanf("%d %d %d", &n, &l, &r);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
        sort(b + 1, b + n + 1);
        ans = 0;
        for (int i = 1; i <= n; i++)
            ans += upper_bound(b + 1, b + n + 1, r - a[i]) - lower_bound(b + 1, b + n + 1, l - a[i]);
        for (int i = 1; i <= n; i++)
            if (l <= (a[i] << 1) && (a[i] << 1) <= r)
                ans--;
        ans >>= 1;
        printf("%lld\n", ans);
    }
    return 0;
}
