#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010;
const long long mod = 1000000007;
const long long inv2 = 500000004;
const long long inv6 = 166666668;
inline int& get(const long long&);
inline long long F(const int&, const long long&);
bool f[maxn];
int p[maxn], cntp;
long long val[maxn << 1];
long long G[2][maxn << 1];
long long sump[2][maxn];
int cnt;
long long n;
int lim;

int main() {
    scanf("%lld", &n);
    lim = (int)sqrtl((long double)n);
    for (int i = 2; i <= lim; i++) {
        if (!f[i]) {
            p[++cntp] = i;
            sump[0][cntp] = sump[0][cntp - 1] + i, sump[1][cntp] = sump[1][cntp - 1] + (long long)i * i % mod;
            if (sump[0][cntp] >= mod)
                sump[0][cntp] -= mod;
            if (sump[1][cntp] >= mod)
                sump[1][cntp] -= mod;
        }
        for (int j = 1; j <= cntp && i * p[j] <= lim; j++) {
            f[i * p[j]] = true;
            if (!(i % p[j]))
                break;
        }
    }
    for (long long l = 1, r; l <= n; l = n / r + 1) {
        r = n / l;
        val[++cnt] = r;
        get(r) = cnt;
        G[0][cnt] = (r % mod * ((r + 1) % mod) % mod * inv2 - 1) % mod;
        G[1][cnt] = (r % mod * ((r + 1) % mod) % mod * ((r << 1ll | 1ll) % mod) % mod * inv6 - 1) % mod;
    }
    for (int i = 1; i <= cntp; i++)
        for (int j = 1; val[j] >= (long long)p[i] * p[i]; j++) {
            G[0][j] -= (G[0][get(val[j] / p[i])] - sump[0][i - 1] + mod) % mod * p[i] % mod;
            G[1][j] -= (G[1][get(val[j] / p[i])] - sump[1][i - 1] + mod) % mod * p[i] % mod * p[i] % mod;
            if (G[0][j] < 0)
                G[0][j] += mod;
            if (G[1][j] < 0)
                G[1][j] += mod;
        }
    for (int i = 1; i <= cnt; i++) {
        G[0][i] = G[1][i] - G[0][i];
        if (G[0][i] < 0)
            G[0][i] += mod;
    }
    for (int i = 1; i <= cntp; i++) {
        sump[0][i] = sump[1][i] - sump[0][i];
        if (sump[0][i] < 0)
            sump[0][i] += mod;
    }
    printf("%lld\n", F(1, n) + 1);
    return 0;
}

int id[2][maxn];
inline int& get(const long long& x) { return x <= lim ? id[0][x] : id[1][n / x]; }

inline long long F(const int& k, const long long& v) {
    if (v < p[k])
        return 0;
    long long ret = G[0][get(v)] - sump[0][k - 1];
    if (ret < 0)
        ret += mod;
    if (k == cntp + 1)
        return (v > p[cntp]) * ret;
    for (int i = k; i <= cntp && (long long)p[i] * p[i] <= v; i++)
        for (long long j = p[i], t = 1; j <= v; j *= p[i], t++) {
            ret += j % mod * ((j - 1) % mod) % mod * (F(i + 1, v / j) + (t != 1)) % mod;
            if (ret >= mod)
                ret -= mod;
        }
    return ret;
}
