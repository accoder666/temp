#include <cstdio>
using namespace std;

const int maxn = 100010;
const long long mod = 323232323;
inline long long C(const int&, const int&);
long long fac[2][maxn];
long long sum[maxn];
int p[maxn], cnt;
bool f[maxn];
int mu[maxn];

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int w, h, n;
    scanf("%d %d %d", &w, &h, &n);
    if (n == 1) {
        printf("%lld\n", (long long)w * h % mod);
        return 0;
    }
    if (w < h)
        w ^= h ^= w ^= h;
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= w; i++) fac[0][i] = fac[0][i - 1] * i % mod;
    long long b = fac[0][w], e = mod - 2;
    fac[1][w] = 1;
    while (e) {
        if (e & 1)
            fac[1][w] = fac[1][w] * b % mod;
        b = b * b % mod, e >>= 1ll;
    }
    for (int i = w - 1; i; i--) fac[1][i] = fac[1][i + 1] * (i + 1) % mod;
    mu[1] = 1;
    for (int i = 2; i <= w; i++) {
        if (!f[i])
            p[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * p[j] <= w; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                mu[i * p[j]] = -mu[i];
            else
                break;
        }
    }
    for (int i = 1; i <= w; i++)
        for (int j = 1; j * i <= w; j++) sum[i * j] = (sum[i * j] + C(i - 1, n - 2) * mu[j]) % mod;
    long long ans = (h * C(w, n) + w * C(h, n)) % mod, s1, s2, tmp;
    for (int i = n - 1; i <= w; i++) {
        s1 = ((long long)(w / i + 1) * (w / i) >> 1ll) % mod,
        s2 = ((long long)(h / i + 1) * (h / i) >> 1ll) % mod;
        tmp =
            (long long)w * h % mod * (w / i) % mod * (h / i) % mod +
            i * (s1 * s2 % mod * i % mod - h * (h / i) % mod * s1 % mod - w * (w / i) % mod * s2 % mod) % mod;
        ans = (ans + (sum[i] * tmp << 1ll)) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}

inline long long C(const int& n, const int& m) {
    if (n < m)
        return 0;
    return fac[0][n] * fac[1][m] % mod * fac[1][n - m] % mod;
}
