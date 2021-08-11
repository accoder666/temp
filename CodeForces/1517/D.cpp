#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 510, maxk = 30;
int a[maxn][maxn], b[maxn][maxn];
int dp[maxn][maxn][maxk];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    if (k & 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) printf("-1 ");
            printf("\n");
        }
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) scanf("%d", a[i] + j);
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", b[i] + j);
    int tmp;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) dp[i][j][0] = 0;
    for (int p = 1; p <= k >> 1; p++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (i != 1 && (tmp = dp[i - 1][j][p - 1] + b[i - 1][j]) < dp[i][j][p])
                    dp[i][j][p] = tmp;
                if (i != n && (tmp = dp[i + 1][j][p - 1] + b[i][j]) < dp[i][j][p])
                    dp[i][j][p] = tmp;
                if (j != 1 && (tmp = dp[i][j - 1][p - 1] + a[i][j - 1]) < dp[i][j][p])
                    dp[i][j][p] = tmp;
                if (j != m && (tmp = dp[i][j + 1][p - 1] + a[i][j]) < dp[i][j][p])
                    dp[i][j][p] = tmp;
            }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) printf("%d ", dp[i][j][k >> 1] << 1);
        printf("\n");
    }
    return 0;
}
