#include <cstdio>
using namespace std;

const int maxn = 1010;
const long long mod = 1000000007;
long long dp[2][maxn][4];
long long fac[2][maxn];
long long g[maxn];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= n; i++) fac[0][i] = fac[0][i - 1] * i % mod;
    long long b = fac[0][n], e = mod - 2;
    fac[1][n] = 1;
    while (e) {
        if (e & 1)
            fac[1][n] = fac[1][n] * b % mod;
        b = b * b % mod, e >>= 1;
    }
    for (int i = n - 1; i; i--) fac[1][i] = fac[1][i + 1] * (i + 1) % mod;
    int cur = 0;
    dp[cur][0][0] = dp[cur][1][1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[cur ^= 1][0][0] = 1;
        for (int j = 1; j <= i; j++) {
            dp[cur][j][0] = (dp[cur ^ 1][j - 1][0] + dp[cur ^ 1][j][0] + dp[cur ^ 1][j][2]) % mod;
            dp[cur][j][2] = (dp[cur ^ 1][j - 1][1] + dp[cur ^ 1][j][1] + dp[cur ^ 1][j][3]) % mod;
            dp[cur][j][1] = (dp[cur ^ 1][j - 1][0] + dp[cur ^ 1][j - 1][2]) % mod;
            dp[cur][j][3] = (dp[cur ^ 1][j - 1][1] + dp[cur ^ 1][j - 1][3]) % mod;
        }
    }
    for (int i = 0; i <= n; i++) g[i] = (dp[cur][i][0] + dp[cur][i][2]) * fac[0][n - i] % mod;
    long long ans = 0;
    for (int i = k; i <= n; i++)
        ans =
            (ans + ((i - k) & 1 ? -1 : 1) * (fac[0][i] * fac[1][k] % mod * fac[1][i - k] % mod) * g[i]) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
