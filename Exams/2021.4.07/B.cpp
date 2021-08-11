#include <cstdio>
using namespace std;

const int maxn = 1010;
long long dp[maxn][maxn], g[maxn];

int main() {
    //    freopen("b.in", "r", stdin);
    //    freopen("b.out", "w", stdout);
    int n;
    long long M;
    long long ans;
    while (scanf("%d %lld", &n, &M) == 2) {
        dp[1][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < i; j++) dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * (n - i)) % M;
        for (int i = 0; i <= n; i++) g[i] = dp[n][i];
        ans = 0;
        for (int i = 0; i <= n; i++) ans = (ans + (i & 1 ? -1 : 1) * g[i]) % M;
        printf("%lld\n", (ans + M) % M);
    }
    return 0;
}
