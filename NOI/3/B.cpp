#include <cstdio>
using namespace std;

const int mod = 9901;
inline int inv(int);

int main() {
    int m, n, ans = 1, a, b;
    scanf("%d %d", &m, &n);
    while (n) {
        a = b = 1;
        for (int i = m % mod - n % mod + 1; i <= m % mod; i++) a = a * i % mod;
        for (int i = 2; i <= n % mod; i++) b = b * i % mod;
        ans = ans * (a * inv(b) % mod) % mod;
        m /= mod, n /= mod;
    }
    printf("%d\n", ans);
    return 0;
}

inline int inv(int b) {
    b %= mod;
    int ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        e >>= 1, b = b * b % mod;
    }
    return ret;
}
