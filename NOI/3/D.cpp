#include <cstdio>
using namespace std;

const long long mod = 9901;
inline long long power(long long, long long e = mod - 2);

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    long long c, v, ans = 1;
    for (long long i = 2; i * i <= a; i++)
        if (!(a % i)) {
            c = 0;
            while (!(a % i)) a /= i, c++;
            v = i % mod;
            if (v == 1)
                ans = ans * (c + 1) % mod;
            else
                ans = ans * (power(v, c * b + 1) - 1) * power(v - 1) % mod;
        }
    if (a != 1) {
        v = a % mod;
        if (v == 1)
            ans = (ans << 1) % mod;
        else
            ans = ans * (power(v, b + 1) - 1) * power(v - 1) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        e >>= 1, b = b * b % mod;
    }
    return ret;
}
