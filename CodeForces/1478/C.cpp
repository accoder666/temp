#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long long d[maxn << 1], tmp[maxn], a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool ans;
    long long sum;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n << 1; i++) scanf("%lld", d + i);
        sort(d + 1, d + (n << 1) + 1);
        ans = true;
        for (int i = 1; i <= n << 1; i += 2)
            if (d[i] != d[i + 1] || (d[i] & 1)) {
                ans = false;
                break;
            } else
                tmp[(i >> 1) + 1] = d[i] >> 1;
        if (!ans) {
            printf("NO\n");
            continue;
        }
        sum = 0;
        for (int i = n; i; i--) {
            if ((tmp[i] - sum) % (long long)i) {
                ans = false;
                break;
            }
            sum += a[i] = (tmp[i] - sum) / (long long)i;
        }
        if (!ans) {
            printf("NO\n");
            continue;
        }
        sort(a + 1, a + n + 1);
        for (int i = 1; i < n; i++)
            if (a[i] == a[i + 1] || a[i] <= 0) {
                ans = false;
                break;
            }
        printf((ans && (a[n] > 0)) ? "YES\n" : "NO\n");
    }
    return 0;
}
