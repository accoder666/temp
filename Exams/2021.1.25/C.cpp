#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
const long long mod = 1000000007;
inline long long inv(long long);
long long m[maxn], d[maxn], v[maxn];

int main() {
    int n, q;
    scanf("%d %d %lld", &n, &q, v);
    for (int i = 1; i <= n; i++) scanf("%lld", m + i);
    for (int i = 1; i <= n; i++) scanf("%lld", d + i), v[i] = max(v[i - 1], d[i - 1]);
    long long ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * min(v[i], m[i]) % mod;
    printf("%d\n", ans);
    int opt, x;
    long long y;
    while (q--) {
        scanf("%d %d %lld", &opt, &x, &y);
        switch (opt) {
            case 0:
                ans = ans * inv(min(v[x], m[x])) % mod * min(v[x], m[x] = y) % mod;
                break;
            case 1:
                d[x] = y;
                for (int i = x + 1; i <= n; i++) {
                    if (max(v[i - 1], d[i - 1]) == v[i])
                        break;
                    ans = ans * inv(min(v[i], m[i])) % mod * min(v[i] = max(v[i - 1], d[i - 1]), m[i]) % mod;
                }
            default:
                break;
        }
        printf("%lld\n", ans);
    }
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
