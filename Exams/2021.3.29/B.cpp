#include <cstdio>
using namespace std;

const int maxn = 1000010;
int dp[2][maxn];

int main() {
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) dp[0][i] = 2;
    int cur = 0, ans = 1;
    while (dp[cur][m] <= n) {
        cur ^= 1, ans++;
        dp[cur][0] = dp[cur ^ 1][0];
        for (int j = 1; j <= m; j++) dp[cur][j] = dp[cur ^ 1][j] + dp[cur ^ 1][j - 1];
    }
    printf("%d\n", ans);
    return 0;
}
