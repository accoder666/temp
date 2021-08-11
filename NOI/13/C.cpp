#include <cstdio>
using namespace std;

const int maxn = 1000000;
long long g[maxn + 10];
int p[maxn + 10], cnt;
bool f[maxn + 10];

int main() {
    g[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!f[i])
            p[++cnt] = i, g[i] = (long long)i * (i - 1) + 1;
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                g[i * p[j]] = g[i] * g[p[j]];
            else {
                g[i * p[j]] = g[i] + (g[i] - g[i / p[j]]) * p[j] * p[j];
                break;
            }
        }
    }
    int t;
    scanf("%d", &t);
    int n;
    while (t--) {
        scanf("%d", &n);
        printf("%lld\n", (g[n] + 1) * (long long)n >> 1ll);
    }
    return 0;
}
