#include <algorithm>
#include <cstdio>
using namespace std;

const long long mod = 19940417;
const long long inv2 = 9970209;
const long long inv6 = 3323403;
inline long long solve(const int&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    if (n < m)
        n ^= m ^= n ^= m;
    long long ans = solve(n) * solve(m) % mod - (long long)m * m % mod * n % mod;
    if (ans < 0)
        ans += mod;
    for (long long l = 1, r; l <= m; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (r - l + 1) * (l + r) % mod * inv2 % mod * ((m * (n / l) + n * (m / l)) % mod) % mod -
               (r * (r + 1) % mod * (r << 1ll | 1ll) - (l - 1) * l % mod * ((l - 1) << 1ll | 1ll)) % mod *
                   inv6 % mod * (n / l) % mod * (m / l) % mod;
        if (ans <= 0)
            ans += mod;
        if (ans >= mod)
            ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}

inline long long solve(const int& n) {
    long long ret = (long long)n * n % mod;
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret -= (n / l) * (l + r) % mod * (r - l + 1) % mod * inv2 % mod;
        if (ret < 0)
            ret += mod;
    }
    return ret;
}
