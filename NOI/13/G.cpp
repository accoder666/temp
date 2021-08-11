#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long long phi[maxn];
int p[maxn], cnt;
bool f[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    if (n < m)
        n ^= m ^= n ^= m;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!f[i])
            p[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            else {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
        }
    }
    for (int i = 2; i <= n; i++) phi[i] += phi[i - 1];
    long long ans = 0;
    for (int l = 1, r; l <= m; l = r + 1)
        ans += (phi[r = min(n / (n / l), m / (m / l))] - phi[l - 1]) * (n / l) * (m / l);
    printf("%lld\n", (ans << 1ll) - (long long)n * m);
    return 0;
}
