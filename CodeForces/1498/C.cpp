#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const int maxn = 1010;
long long c[maxn], tmp[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k;
    long long ans;
    while (t--) {
        scanf("%d %d", &n, &k);
        if (k == 1) {
            printf("1\n");
            continue;
        }
        if (n == 1) {
            printf("2\n");
            continue;
        }
        if (k == 2) {
            printf("%d\n", n + 1);
            continue;
        }
        ans = n + 1;
        for (int i = 1; i <= n; i++) c[i] = n - i;
        for (int i = 2, dir = -1; i < k; i++, dir = -dir) {
            for (int j = 1; j <= n; j++) ans = (ans + c[j]) % mod;
            if (dir == 1) {
                for (int j = 1; j <= n; j++) tmp[j] = c[j];
                for (int j = n - 1; j; j--) c[j] = (c[j] + c[j + dir]) % mod;
                for (int j = 1; j <= n; j++) c[j] = (c[j] - tmp[j] + mod) % mod;
            } else {
                for (int j = 1; j <= n; j++) tmp[j] = c[j];
                for (int j = 2; j <= n; j++) c[j] = (c[j] + c[j + dir]) % mod;
                for (int j = 1; j <= n; j++) c[j] = (c[j] - tmp[j] + mod) % mod;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
