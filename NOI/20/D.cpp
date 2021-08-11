#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;

const long long mod = 1000000007;
const long long inv2 = 500000004;
const int maxn = 100010, maxt = 1000010;
long long solve(const int&, const long long&);
long long phi[maxt], sum[maxt];
int p[maxt], cnt;
bool f[maxt];
int t;

int main() {
    int n;
    long long m;
    scanf("%d %lld", &n, &m);
    t = (int)powl((long double)m, (long double)2.0 / 3.0);
    if (t < n)
        t = n;
    phi[1] = 1;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            phi[i] = i - 1, p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            else {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
        }
    }
    for (int i = 1; i <= t; i++) {
        sum[i] = sum[i - 1] + phi[i];
        if (sum[i] >= mod)
            sum[i] -= mod;
    }
    long long ans = 0;
    int k, c, v;
    for (int i = 1; i <= n; i++) {
        k = i, c = v = 1;
        for (int j = 2; j * j <= i; j++)
            if (!(k % j)) {
                k /= j, v *= j;
                while (!(k % j)) k /= j, c *= j;
            }
        v *= k;
        ans += solve(v, m) * c % mod;
        if (ans >= mod)
            ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}

unordered_map<long long, long long> s;
long long S(const long long& n) {
    if (n <= t)
        return sum[n];
    if (s.count(n))
        return s[n];
    long long ret = n % mod * ((n + 1) % mod) % mod * inv2 % mod;
    for (long long l = 2, r; l <= n; l = r + 1) {
        ret -= ((r = n / (n / l)) - l + 1) % mod * S(n / l) % mod;
        if (ret < 0)
            ret += mod;
    }
    return s[n] = ret;
}

unordered_map<long long, long long> M[maxn];
long long solve(const int& n, const long long& m) {
    if (n == 1)
        return S(m);
    if (!m)
        return 0;
    if (m == 1)
        return phi[n];
    if (M[n].count(m))
        return M[n][m];
    long long ret = 0;
    for (int i = 1; i * i <= n; i++)
        if (!(n % i)) {
            ret += phi[n / i] * solve(i, m / i) % mod;
            if (i * i != n)
                ret += phi[i] * solve(n / i, m / (n / i)) % mod;
            while (ret >= mod) ret -= mod;
        }
    return M[n][m] = ret;
}
