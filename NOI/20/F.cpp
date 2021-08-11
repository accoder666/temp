#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 400000;
inline int& get(const long long&);
inline long long F(const int&, const long long&);
bool f[maxn + 10];
int p[maxn + 10], cntp;
long long val[(maxn << 1) + 10];
long long G[(maxn << 1) + 10];
int cnt;
long long n;
int lim;

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 2; i <= maxn; i++) {
        if (!f[i])
            p[++cntp] = i;
        for (int j = 1; j <= cntp && i * p[j] <= maxn; j++) {
            f[i * p[j]] = true;
            if (!(i % p[j]))
                break;
        }
    }
    while (t--) {
        scanf("%lld", &n);
        lim = (int)sqrtl((long double)n);
        for (cntp = 1; p[cntp] <= lim; cntp++) continue;
        cntp--;
        cnt = 0;
        for (long long l = 1, r; l <= n; l = n / r + 1) {
            r = n / l;
            val[++cnt] = r;
            get(r) = cnt;
            G[cnt] = r - 1;
        }
        for (int i = 1; i <= cntp; i++)
            for (int j = 1; val[j] >= (long long)p[i] * p[i]; j++) G[j] -= G[get(val[j] / p[i])] - i + 1;
        for (int i = 1; i <= cnt; i++) G[i] *= 4;
        printf("%lld\n", F(1, n) + 1);
    }
    return 0;
}

int id[2][maxn + 10];
inline int& get(const long long& x) { return x <= lim ? id[0][x] : id[1][n / x]; }

inline long long F(const int& k, const long long& v) {
    if (v < p[k])
        return 0;
    long long ret = G[get(v)] - 4 * (k - 1);
    if (k == cntp + 1)
        return (v > p[cntp]) * ret;
    for (int i = k; i <= cntp && (long long)p[i] * p[i] <= v; i++)
        for (long long j = p[i], t = 1; j <= v; j *= p[i], t++)
            ret += (3 * t + 1) * (F(i + 1, v / j) + (t != 1));
    return ret;
}
