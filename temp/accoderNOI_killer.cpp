// Problem : http://47.92.197.167:5283/contest/58/problem/3

#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

const int maxn = 100010;
const long long mod = 1000000007;
inline long long inv(long long);
long long m[maxn], d[maxn], v[maxn];
long long ans[maxn];

const int MX = (1 << 26);
inline unsigned int rnd(void);
int array[MX - 1100000];

int main() {
    clock_t b = clock();
    int n, q;
    scanf("%d %d %lld", &n, &q, v);
    for (int i = 1; i <= n; i++) scanf("%lld", m + i);
    for (int i = 1; i <= n; i++) scanf("%lld", d + i), v[i] = max(v[i - 1], d[i - 1]);
    long long a = 1;
    for (int i = 1; i <= n; i++) a = a * min(v[i], m[i]) % mod;
    ans[0] = a;
    int opt, x;
    long long y;
    for (int i = 1; i <= q; i++) {
        scanf("%d %d %lld", &opt, &x, &y);
        switch (opt) {
            case 0:
                a = a * inv(min(v[x], m[x])) % mod * min(v[x], m[x] = y) % mod;
                break;
            case 1:
                d[x] = y;
                for (int j = x + 1; j <= n; j++) {
                    if (max(v[j - 1], d[j - 1]) == v[j])
                        break;
                    a = a * inv(min(v[j], m[j])) % mod * min(v[j] = max(v[j - 1], d[j - 1]), m[j]) % mod;
                }
            default:
                break;
        }
        ans[i] = a;
    }
    unsigned int tmp;
    for (int i = 0; clock() - b < CLOCKS_PER_SEC * 9.95; i++) {
        tmp = rnd();
        if (tmp + 1100000 < MX)
            array[tmp] = i;
    }
    for (int i = 0; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}

inline long long inv(long long b) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}

inline unsigned int rnd(void) {
    static unsigned int sed = 0;
    return (sed = (sed * 233 + 19260421)) & (MX - 1);
}
