#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;

const long long mod = 1000000007;
const long long inv2 = 500000004;
const long long inv6 = 166666668;
const int maxn = 5000010;
long long S(const long long&);
long long val[maxn];
int p[maxn], cnt;
bool f[maxn];
int t;

int main() {
    long long n;
    scanf("%lld", &n);
    t = (int)powl((long double)n, (long double)2.0 / 3.0);
    val[1] = 1;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            val[i] = i - 1, p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                val[i * p[j]] = val[i] * (p[j] - 1);
            else {
                val[i * p[j]] = val[i] * p[j];
                break;
            }
        }
    }
    for (int i = 2; i <= t; i++) {
        val[i] = val[i - 1] + (long long)i * i % mod * val[i] % mod;
        if (val[i] >= mod)
            val[i] -= mod;
    }
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (l + r) % mod * ((r - l + 1) % mod) % mod * inv2 % mod * S(n / l) % mod;
        if (ans >= mod)
            ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}

unordered_map<long long, long long> M;
long long S(const long long& n) {
    if (n <= t)
        return val[n];
    if (M.count(n))
        return M[n];
    long long ret = n % mod * ((n + 1) % mod) % mod * inv2 % mod;
    ret = ret * ret % mod;
    for (long long l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret -= (r % mod * ((r + 1) % mod) % mod * (((r << 1ll) + 1) % mod) % mod * inv6 % mod -
                (l - 1) % mod * (l % mod) % mod * (((l << 1ll) - 1) % mod) % mod * inv6 % mod + mod) %
               mod * S(n / l) % mod;
        if (ret < 0)
            ret += mod;
    }
    return M[n] = ret;
}
