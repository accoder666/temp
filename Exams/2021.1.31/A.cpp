#include <cstdio>
#include <unordered_set>
using namespace std;

const long long mod = 1000000007;
inline long long power(long long, long long);
unordered_set<int> S;

int main() {
    freopen("str.in", "r", stdin);
    freopen("str.out", "w", stdout);
    int n, m, a;
    scanf("%d %d %d", &n, &m, &a);
    long long ans = 0;
    if (a == 2) {
        int lim = 1 << n, mask = (1 << m) - 1;
        for (int i = 0; i < lim; i++) {
            S.clear();
            for (int j = i, c = 0; c + m <= n; j >>= 1, c++) S.insert(j & mask);
            ans += S.size();
            if (ans >= mod)
                ans -= mod;
        }
        printf("%lld\n", ans);
        return 0;
    }
    if (m == n)
        printf("%lld\n", power(a, n));
    else if (m == n - 1)
        printf("%lld\n", ((power(a, n) << 1) - a + mod) % mod);
    else if (m == n - 2)
        printf(
            "%lld\n",
            (a + (a * (a - 1) % mod * 3 << 1) + 3 * ((power(a, n) - a - a * (a - 1) % mod * 3) % mod)) % mod);
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
