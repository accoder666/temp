#include <algorithm>
#include <cstdio>
using namespace std;

const long long mod = 100000009;
const int maxn = 10000000;
long long g[maxn + 10];
int p[maxn + 10], cnt;
bool flag[maxn + 10];
inline long long S(const long long&);

int main() {
    g[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!flag[i])
            p[++cnt] = i, g[i] = mod + 1 - i;
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) {
            flag[i * p[j]] = true;
            if (i % p[j])
                g[i * p[j]] = g[i] * g[p[j]] % mod;
            else {
                g[i * p[j]] = g[i];
                break;
            }
        }
    }
    for (int i = 1; i <= maxn; i++) {
        g[i] = g[i - 1] + (long long)i * g[i] % mod;
        if (g[i] >= mod)
            g[i] -= mod;
    }
    int t;
    scanf("%d", &t);
    int n, m;
    long long ans;
    while (t--) {
        scanf("%d %d", &n, &m);
        ans = 0;
        for (int l = 1, r; l <= min(n, m); l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            ans += (g[r] - g[l - 1]) * S(n / l) % mod * S(m / l) % mod;
            if (ans >= mod)
                ans -= mod;
            if (ans < 0)
                ans += mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

inline long long S(const long long& v) { return (v * (v + 1) >> 1ll) % mod; }
