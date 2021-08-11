#include <cstdio>
using namespace std;

const int maxn = 2000010;
const long long mod = 998244353;
inline long long inverse(long long);
long long inv[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long ans = inv[1] = 1;
    for (int i = 2; i <= n; i++) ans += (inv[i] = (mod - mod / i) * inv[mod % i] % mod);
    ans %= mod;
    ans = (long long)(n + m + 1) * (m * ans % mod + 1) % mod * inverse(m + 1) % mod;
    printf("%lld\n", ans);
    return 0;
}

inline long long inverse(long long v) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * v % mod;
        v = v * v % mod, e >>= 1;
    }
    return ret;
}
