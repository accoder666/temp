#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;

const long long mod = 1000000007;
const long long inv2 = 500000004;
const int maxn = 5000010;
long long S(const long long&);
long long phi[maxn];
int p[maxn], cnt;
bool f[maxn];
int t;

int main() {
    long long n;
    scanf("%lld", &n);
    t = (int)powl((long double)n, (long double)2.0 / 3.0);
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
    for (int i = 2; i <= t; i++) {
        phi[i] += phi[i - 1];
        if (phi[i] >= mod)
            phi[i] -= mod;
    }
    printf("%lld\n", S(n));
    return 0;
}

unordered_map<long long, long long> M;
long long S(const long long& n) {
    if (n <= t)
        return phi[n];
    if (M.count(n))
        return M[n];
    long long ret = n % mod * ((n + 1) % mod) % mod * inv2 % mod;
    for (long long l = 2, r; l <= n; l = r + 1) {
        ret -= ((r = n / (n / l)) - l + 1) % mod * S(n / l) % mod;
        if (ret < 0)
            ret += mod;
    }
    return M[n] = ret;
}
