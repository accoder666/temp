#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 50000;
int e[maxn + 10], mu[maxn + 10];
long long d[maxn + 10];
int p[maxn + 10], cnt;
bool f[maxn + 10];

int main() {
    d[1] = mu[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!f[i])
            p[++cnt] = i, d[i] = 2, e[i] = 1, mu[i] = -1;
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                d[i * p[j]] = d[i] << 1, e[i * p[j]] = 1, mu[i * p[j]] = -mu[i];
            else {
                e[i * p[j]] = e[i] + 1;
                d[i * p[j]] = d[i] / e[i * p[j]] * (e[i * p[j]] + 1);
                break;
            }
        }
    }
    for (int i = 2; i <= maxn; i++) d[i] += d[i - 1], mu[i] += mu[i - 1];
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
            ans += (mu[r = min(n / (n / l), m / (m / l))] - mu[l - 1]) * d[n / l] * d[m / l];
        printf("%lld\n", ans);
    }
    return 0;
}
