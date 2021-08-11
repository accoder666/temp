#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10010;
const long long mod = 1000000007;
const long long sqrt2 = 59713600;
inline long long power(long long, long long);
char N[maxn];

int main() {
    scanf("%s", N);
    int len = strlen(N);
    long long n = 0;
    for (int i = 0; i < len; i++) n = ((n << 3) + (n << 1) + (long long)(N[i] - '0')) % (mod - 1);
    printf("%lld\n", ((sqrt2 - 1) * power(2 * sqrt2, mod - 2) % mod * power(1 - sqrt2 + mod, n - 1) +
                      (sqrt2 + 1) * power(2 * sqrt2, mod - 2) % mod * power(sqrt2 + 1, n - 1)) %
                         mod);
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}
