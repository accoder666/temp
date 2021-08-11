#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 10000000;
int p[maxn + 10], cnt;
bool f[maxn + 10];
int mu[maxn + 10];
long long g[maxn + 10];

int main() {
    mu[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!f[i])
            p[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                mu[i * p[j]] = -mu[i];
            else
                break;
        }
    }
    for (int i = 1; i <= maxn; i++)
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) g[i * p[j]] += mu[i];
    for (int i = 2; i <= maxn; i++) g[i] += g[i - 1];
    int t;
    scanf("%d", &t);
    int n, m;
    long long ans;
    while (t--) {
        scanf("%d %d", &n, &m);
        if (n < m)
            n ^= m ^= n ^= m;
        ans = 0;
        for (int l = 1, r; l <= m; l = r + 1)
            ans += (g[r = min(n / (n / l), m / (m / l))] - g[l - 1]) * (n / l) * (m / l);
        printf("%lld\n", ans);
    }
    return 0;
}
