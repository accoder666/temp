#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 2010;
const long long mod = 1000000009;
long long a[maxn], b[maxn];
long long dp[2][maxn], g[maxn];
long long fac[2][maxn];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    if ((n + k) & 1) {
        printf("0\n");
        return 0;
    }
    k = (n + k) >> 1;
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    for (int i = 1; i <= n; i++) scanf("%lld", b + i);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    int cur = 0, v = 0;
    dp[cur][0] = 1;
    for (int i = 1; i <= n; i++) {
        cur ^= 1;
        while (v < n && b[v + 1] < a[i]) v++;
        for (int j = 0; j <= i; j++)
            dp[cur][j] = (dp[cur ^ 1][j] + (j ? (v - (j - 1)) * dp[cur ^ 1][j - 1] : 0)) % mod;
    }
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= n; i++) fac[0][i] = fac[0][i - 1] * i % mod;
    long long base = fac[0][n], e = mod - 2;
    fac[1][n] = 1;
    while (e) {
        if (e & 1)
            fac[1][n] = fac[1][n] * base % mod;
        base = base * base % mod, e >>= 1;
    }
    for (int i = n - 1; i; i--) fac[1][i] = fac[1][i + 1] * (i + 1) % mod;
    for (int i = 0; i <= n; i++) g[i] = dp[cur][i] * fac[0][n - i] % mod;
    long long ans = 0;
    for (int i = k; i <= n; i++)
        ans =
            (ans + ((i - k) & 1 ? -1 : 1) * (fac[0][i] * fac[1][k] % mod * fac[1][i - k] % mod) * g[i]) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
