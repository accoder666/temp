#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 4000000;
signed int g[maxn + 10];
int p[maxn + 10], cnt;
bool f[maxn + 10];

int main() {
    g[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!f[i])
            p[++cnt] = i, g[i] = 1 - i;
        for (int j = 1; j <= cnt && i * p[j] <= maxn; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                g[i * p[j]] = g[i] * g[p[j]];
            else {
                if (i % (p[j] * p[j]))
                    g[i * p[j]] = -g[i / p[j]] * p[j];
            }
        }
    }
    for (int i = 1; i <= maxn; i++) g[i] = g[i - 1] + g[i] * i;
    int t;
    scanf("%d", &t);
    int n, m;
    signed int ans, N, M;
    while (t--) {
        scanf("%d %d", &n, &m);
        ans = 0;
        for (int l = 1, r; l <= min(n, m); l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            N = n / l, M = m / l;
            ans += (g[r] - g[l - 1]) * N * M * (N + 1) * (M + 1) >> 2;
        }
        printf("%u\n", ans & ((1 << 30) - 1));
    }
    return 0;
}
