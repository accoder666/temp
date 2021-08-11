#include <cstdio>
using namespace std;

const int maxn = 1000010;
const long long mod = 1000000007;
long long fac[2][maxn];
inline long long C(int, int);

int main() {
    int n;
    scanf("%d", &n);
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= n; i++) fac[0][i] = fac[0][i - 1] * i % mod;
    fac[1][n] = 1;
    long long b = fac[0][n], e = mod - 2;
    while (e) {
        if (e & 1)
            fac[1][n] = fac[1][n] * b % mod;
        b = b * b % mod, e >>= 1;
    }
    for (int i = n - 1; i; i--) fac[1][i] = fac[1][i + 1] * (i + 1) % mod;
    long long ans = 0, tmp;
    int p = (n + 1) >> 1;
    if (p & 1)
        p++;
    for (int i = p; i <= n; i += 2) {
        tmp = fac[0][i] << 1;
        if (tmp >= mod)
            tmp -= mod;
        if (i != n)
            tmp = tmp * (C(i, n - i) + C(i - 1, n - i - 1)) % mod;
        ans += tmp;
        if (ans >= mod)
            ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}

inline long long C(const int n, const int k) { return fac[0][n] * fac[1][k] % mod * fac[1][n - k] % mod; }
