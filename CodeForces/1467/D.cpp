#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const int maxn = 5010;
long long dp[2][maxn], val[maxn];
long long a[maxn];

int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    int cur = 0;
    for (int i = 1; i <= n; i++) dp[cur][i] = val[i] = 1;
    for (int i = 1; i <= k; i++) {
        cur ^= 1;
        for (int j = 1; j <= n; j++) {
            dp[cur][j] = (j == 1 ? 0 : dp[cur ^ 1][j - 1]) + (j == n ? 0 : dp[cur ^ 1][j + 1]);
            if (dp[cur][j] >= mod)
                dp[cur][j] -= mod;
            val[j] = dp[cur][j] * dp[cur][j] % mod + dp[cur][j];
            if (val[j] >= mod)
                val[j] -= mod;
        }
    }
    for (int i = 1; i <= n; i++) printf("%lld ", val[i]);
    printf("\n");
    long long ans = 0;
    for (int i = 1; i <= n; i++) scanf("%lld", a + i), ans = (ans + a[i] * val[i]) % mod;
    int p;
    long long x;
    while (q--) {
        scanf("%d %lld", &p, &x);
        ans = (ans + (x - a[p] + mod) % mod * val[p] % mod + mod) % mod;
        a[p] = x;
        printf("%lld\n", ans);
    }
    return 0;
}
