#include <cstdio>
using namespace std;

const int maxk = 10000010;
const long long mod = 998244353;
inline long long power(long long, long long);
long long inv[maxk];

int main() {
    freopen("qian.in", "r", stdin);
    freopen("qian.out", "w", stdout);
    long long n, k, a;
    scanf("%lld %lld %lld", &n, &k, &a);
    if (n < k) {
        printf("0\n");
        return 0;
    }
    inv[1] = 1;
    for (int i = 2; i <= k; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    if (a == 1) {
        long long ans = 1;
        for (long long i = n - k + 1; i <= n; i++) ans = ans * i % mod;
        for (int i = 1; i <= k; i++) ans = ans * inv[i] % mod;
        printf("%lld\n", ans);
        return 0;
    }
    long long val = power(a - 1, mod - 2);
    long long lc, c = 1, s = (mod + 1 - power(a, n + 1)) % mod * power(mod + 1 - a % mod, mod - 2) % mod;
    n %= mod;
    for (int i = 1; i < k; i++) {
        lc = c;
        c = c * (n - i + 1) % mod * inv[i] % mod;
        s = (s - c - lc + (mod << 1)) % mod * val % mod;
    }
    printf("%lld\n", (s - c + mod) % mod);
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}
