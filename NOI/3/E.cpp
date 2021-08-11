#include <cstdio>
using namespace std;

const int maxn = 40000;
const long long mod = 999911659;
const long long p[4] = { 2, 3, 4679, 35617 };
inline long long power(long long, long long, const long long&);
inline long long Lucas(long long, long long, const int&);
long long fac[maxn + 10];

int main() {
    long long n, g;
    scanf("%lld %lld", &n, &g);
    g %= mod;
    if (!g) {
        printf("0\n");
        return 0;
    }
    fac[0] = 1;
    long long val[4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= maxn; j++) fac[j] = (fac[j - 1] * j) % p[i];
        for (int j = 1; (long long)j * j <= n; j++)
            if (!(n % j)) {
                val[i] = (val[i] + Lucas(n, j, i)) % p[i];
                if ((long long)j * j != n)
                    val[i] = (val[i] + Lucas(n, n / j, i)) % p[i];
            }
    }
    long long ans = 0;
    for (int i = 0; i < 4; i++)
        ans = (ans + val[i] * ((mod - 1) / p[i]) % (mod - 1) * power((mod - 1) / p[i], p[i] - 2, p[i])) %
              (mod - 1);
    printf("%lld\n", power(g, ans, mod));
    return 0;
}

inline long long power(long long b, long long e, const long long& P) {
    b %= P, e %= P - 1;
    long long val = 1;
    while (e) {
        if (e & 1)
            val = (val * b) % P;
        b = (b * b) % P, e >>= 1;
    }
    return val;
}

inline long long Lucas(long long n, long long m, const int& i) {
    long long C = 1;
    while (m) {
        if (n % p[i] >= m % p[i])
            C = C *
                (((fac[n % p[i]] % p[i]) * power(fac[m % p[i]], p[i] - 2, p[i]) % p[i]) *
                 power(fac[n % p[i] - m % p[i]], p[i] - 2, p[i])) %
                p[i];
        else
            return 0;
        n /= p[i], m /= p[i];
    }
    return C;
}
