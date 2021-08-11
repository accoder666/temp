#include <cstdio>
using namespace std;

const int maxn = 100000;
const long long mod = 1000000007;
long long fac[2][maxn + 10];
inline long long inv(long long);
inline long long C(int, int);

int main() {
    int t;
    scanf("%d", &t);
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= maxn; i++) fac[0][i] = fac[0][i - 1] * i % mod;
    fac[1][maxn] = inv(fac[0][maxn]);
    for (int i = maxn - 1; i; i--) fac[1][i] = fac[1][i + 1] * (i + 1) % mod;
    int n, k;
    long long ans;
    while (t--) {
        scanf("%d %d", &n, &k);
        ans = 1;
        for (int i = 1; n - (k - 1) * (i - 1) >= i; i++)
            ans = (ans + C(n - (k - 1) * (i - 1), i) % mod * inv(C(n, i))) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}

inline long long inv(long long b) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}

inline long long C(const int n, const int k) { return fac[0][n] * fac[1][k] % mod * fac[1][n - k] % mod; }
