#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 400000;
inline long long solve(const long long&);
bool f[maxn + 10];
int p[maxn + 10], cntp;
long long val[(maxn << 1) + 10];
long long G[(maxn << 1) + 10];
int cnt;

int main() {
    long long l, r;
    scanf("%lld %lld", &l, &r);
    int t = (int)sqrt(r) + 100;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            p[++cntp] = i;
        for (int j = 1; j <= cntp && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (!(i % p[j]))
                break;
        }
    }
    printf("%lld\n", solve(r) - solve(l - 1));
    return 0;
}

long long n;
int id[2][maxn + 10], lim;
inline int& get(const long long& x) { return x <= lim ? id[0][x] : id[1][n / x]; }

inline long long F(const int& k, const long long& v) {
    if (v < p[k])
        return 0;
    long long ret = 0;
    for (int i = k; i <= cntp && (long long)p[i] * p[i] <= v; i++)
        for (long long j = p[i]; j * p[i] <= v; j *= p[i])
            ret += F(i + 1, v / j) + (G[get(v / j)] - (i - 1)) * p[i];
    return ret;
}

inline long long solve(const long long& t) {
    n = t, lim = (int)sqrtl((long double)n);
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
    return F(1, n) + 1;
}
