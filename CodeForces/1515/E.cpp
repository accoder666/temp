#include <cstdio>
using namespace std;

const int maxn = 410;
long long C[maxn][maxn], pow[maxn];
long long dp[maxn][maxn];

int main() {
    int n;
    long long M;
    scanf("%d %lld", &n, &M);
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if (C[i][j] >= M)
                C[i][j] -= M;
        }
    }
    pow[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow[i] = pow[i - 1] << 1;
        if (pow[i] >= M)
            pow[i] -= M;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            for (int k = 1; i + k <= n + 1; k++)
                dp[i + k][j + k] = (dp[i + k][j + k] + dp[i - 1][j] * pow[k - 1] % M * C[j + k][k]) % M;
    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += dp[n + 1][i];
        if (ans >= M)
            ans -= M;
    }
    printf("%lld\n", ans);
    return 0;
}
