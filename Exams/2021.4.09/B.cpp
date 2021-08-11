#include <cstdio>
#include <cstring>
using namespace std;

const long long mod = 1000000007;
const int maxn = 100010;
long long f[maxn], g[maxn], v[maxn];
inline void solve(const long long*, const long long*, long long*);
int n;

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int k;
    while (t--) {
        scanf("%d %d", &n, &k), k--;
        for (int i = 1; i <= n; i++) scanf("%lld", f + i), g[i] = v[i] = 1;
        while (k) {
            if (k & 1)
                solve(g, v, g);
            solve(v, v, v), k >>= 1;
        }
        solve(f, g, g);
        for (int i = 1; i <= n; i++) printf("%lld ", g[i]);
        printf("\n");
    }
    return 0;
}

inline void solve(const long long* x, const long long* y, long long* ret) {
    static long long val[maxn];
    memset(val, 0, sizeof(val));
    for (int i = 1; i <= n; i++)
        for (int j = 1; i * j <= n; j++) val[i * j] = (val[i * j] + x[i] * y[j]) % mod;
    for (int i = 1; i <= n; i++) ret[i] = val[i];
    return;
}
