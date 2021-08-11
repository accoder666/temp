#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 300010;
int k[maxn];
long long c[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m;
    long long ans;
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", k + i);
        for (int i = 1; i <= m; i++) scanf("%lld", c + i);
        sort(k + 1, k + n + 1);
        ans = 0;
        for (int i = n; i; i--)
            if (k[i] > n - i + 1)
                ans += c[n - i + 1];
            else
                ans += c[k[i]];
        printf("%lld\n", ans);
    }
    return 0;
}
