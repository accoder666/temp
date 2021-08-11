#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 50000;
int p[maxn + 10], cnt;
bool f[maxn + 10];
int mu[maxn + 10];

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
    for (int i = 2; i <= maxn; i++) mu[i] += mu[i - 1];
    int n;
    scanf("%d", &n);
    int a, b, d, ans;
    while (n--) {
        scanf("%d %d %d", &a, &b, &d);
        a /= d, b /= d;
        if (a < b)
            a ^= b ^= a ^= b;
        ans = 0;
        for (int l = 1, r; l <= b; l = r + 1)
            ans += (mu[r = min(a / (a / l), b / (b / l))] - mu[l - 1]) * (a / l) * (b / l);
        printf("%d\n", ans);
    }
    return 0;
}
