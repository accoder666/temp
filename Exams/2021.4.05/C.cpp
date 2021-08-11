#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const int maxn = 5010;
inline long long inv(long long);
long long a[maxn][maxn];
int p[maxn];

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", a[1] + i);
    for (int i = 1; i <= n; i++) scanf("%d", p + i);
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = a[i - 1][p[j]];
    long long ans = 1, c;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            while (a[j][i]) {
                c = a[i][i] / a[j][i];
                for (int k = i; k <= n; k++) a[i][k] = (a[i][k] - c * a[j][k] % mod + mod) % mod;
                for (int k = i; k <= n; k++) a[i][k] ^= a[j][k] ^= a[i][k] ^= a[j][k];
                ans = -ans;
            }
        ans = ans * a[i][i] % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}

inline long long inv(long long v) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * v % mod;
        v = v * v % mod, e >>= 1;
    }
    return ret;
}
