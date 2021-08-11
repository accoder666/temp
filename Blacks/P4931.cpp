#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 5000010;
const long long mod = 998244353;
long long v[maxn], fac[2][maxn], p[maxn];
struct query {
    int n, k;
};
query Q[maxn];

int main() {
    int T;
    scanf("%d", &T);
    int m1 = 0, m2 = 0, m3 = 0;
    for (int i = 1; i <= T; i++) {
        scanf("%d %d", &Q[i].n, &Q[i].k);
        m1 = max(m1, Q[i].n - Q[i].k), m2 = max(m2, Q[i].n), m3 = max(m3, Q[i].k);
    }
    v[0] = 1, v[1] = 0;
    for (long long i = 2; i <= m1; i++)
        v[i] = (((i * i - i) << 2ll) % mod * v[i - 1] % mod +
                ((((i * i) % mod * i - (i * i << 1ll) % mod + i + mod) << 3ll) % mod) * v[i - 2] % mod) %
               mod;
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= m2; i++) fac[0][i] = ((long long)i * fac[0][i - 1]) % mod;
    fac[1][m2] = 1;
    long long b = fac[0][m2], e = mod - 2;
    while (e) {
        if (e & 1ll)
            fac[1][m2] = fac[1][m2] * b % mod;
        e >>= 1ll, b = b * b % mod;
    }
    for (int i = m2 - 1; i; i--) fac[1][i] = fac[1][i + 1] * ((long long)i + 1) % mod;
    p[0] = 1;
    for (int i = 1; i <= m3; i++) p[i] = (p[i - 1] << 1ll) % mod;
    long long C;
    for (int i = 1; i <= T; i++) {
        C = ((fac[0][Q[i].n] * fac[1][Q[i].k]) % mod * fac[1][Q[i].n - Q[i].k]) % mod;
        printf("%lld\n",
               (((C * C % mod) * v[Q[i].n - Q[i].k] % mod) * fac[0][Q[i].k] % mod) * p[Q[i].k] % mod);
    }
    return 0;
}
