
// Problem : CF913F Strongly Connected Tournament
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/CF913F
// Memory Limit : 250 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

namespace inverse {
using namespace std;
template <typename T>
void exgcd(const T& a, const T& b, T& g, T& x, T& y) {
    if (b) {
        exgcd(b, a % b, g, y, x);
        y -= x * (a / b);
        return;
    }
    g = a, x = 1, y = 0;
    return;
}
template <typename T>
T Inverse(const T& a, const T& p) {
    T g, x, y;
    exgcd(a, p, g, x, y);
    x %= p;
    if (x < 0)
        x += p;
    return x;
}
}  // namespace inverse
using namespace inverse;

#include <cstdio>
using namespace std;

const int maxn = 2001;
const long long mod = 998244353;
long long dp[maxn], f[maxn][maxn], g[maxn], h[maxn];
long long power[2][maxn];

int main() {
    int n;
    long long a, b;
    scanf("%d %lld %lld", &n, &a, &b);
    if (n <= 2) {
        if (n == 1)
            printf("0\n");
        else
            printf("1\n");
        return 0;
    }
    long long p = (a * Inverse(b, mod)) % mod;
    power[0][0] = power[1][0] = 1;
    for (int i = 1; i <= n; i++)
        power[0][i] = (power[0][i - 1] * p) % mod, power[1][i] = (power[1][i - 1] * (mod - p + 1)) % mod;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j - 1] * power[0][i - j] + f[i - 1][j] * power[1][j]) % mod;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) g[i] = (g[i] + g[j] * f[i][j]) % mod;
        g[i] = (mod - g[i] + 1) % mod;
    }
    long long t;
    for (int i = 3; i <= n; i++) {
        t = 0;
        for (int j = 1; j < i; j++) t = (t + (f[i][j] * g[j] % mod) * (dp[j] + h[i - j]) % mod) % mod;
        dp[i] = ((t + (((i * (i - 1) / 2) % mod) % mod)) * Inverse(mod + 1 - g[i], mod) % mod) % mod;
        h[i] = ((dp[i] * g[i]) % mod + t) % mod;
    }
    printf("%lld\n", (dp[n] + mod) % mod);
    return 0;
}
