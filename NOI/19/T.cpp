#include <cstdio>
using namespace std;

inline long long mul(const long long&, const long long&, const long long&);
inline long long pow(long long, long long, const long long&);

int main() {
    long long n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    printf("%lld\n", mul(pow(n, m - 1, p), pow(m, n - 1, p), p));
    return 0;
}

inline long long mul(const long long& x, const long long& y, const long long& mod) {
    return (x * y - (long long)((long double)x / mod * y) * mod + mod) % mod;
}

inline long long pow(long long b, long long e, const long long& mod) {
    long long ret = 1;
    b %= mod;
    while (e) {
        if (e & 1)
            ret = mul(ret, b, mod);
        b = mul(b, b, mod), e >>= 1;
    }
    return ret;
}
