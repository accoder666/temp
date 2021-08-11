#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;

const int maxn = 5000010;
const long long mod = 1000000007;
const long long inv2 = 500000004;
const long long inv6 = 166666668;
long long S(const long long&);
long long g[maxn];
int p[maxn], cnt;
bool f[maxn];
int t;

int main() {
    freopen("divisor.in", "r", stdin);
    freopen("divisor.out", "w", stdout);
    long long n;
    scanf("%lld", &n);
    t = (int)powl((long double)n, (long double)2 / 3);
    g[1] = 1;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            p[++cnt] = i, g[i] = i - 1;
        for (int j = 1; j <= cnt && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                g[i * p[j]] = g[i] * (p[j] - 1);
            else {
                g[i * p[j]] = g[i] * p[j];
                break;
            }
        }
    }
    for (int i = 1; i <= t; i++) {
        g[i] = g[i - 1] + g[i] * i % mod;
        if (g[i] >= mod)
            g[i] -= mod;
    }
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        ans = ans + ((r = n / (n / l)) - l + 1) % mod * S(n / l) % mod;
        if (ans >= mod)
            ans -= mod;
    }
    ans = ((ans - n + mod) * 3 % mod * inv2 % mod + n) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}

unordered_map<long long, long long> M;
long long S(const long long& n) {
    if (n <= t)
        return g[n];
    if (M.count(n))
        return M[n];
    long long ret = 0;
    for (long long l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret += (l + r) % mod * ((r - l + 1) % mod) % mod * inv2 % mod * S(n / l) % mod;
        if (ret >= mod)
            ret -= mod;
    }
    ret = n % mod * ((n + 1) % mod) % mod * ((n << 1 | 1) % mod) % mod * inv6 % mod - ret % mod;
    return M[n] = (ret + mod) % mod;
}
