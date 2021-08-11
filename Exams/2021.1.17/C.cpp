#include <cstdio>
using namespace std;

const long long mod = 323232323;
const int maxn = 10010;
long long dp[maxn][maxn];
bool flag[maxn][maxn];
int a[maxn];

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), dp[i][i] = a[i] == 1;
    int tmp;
    for (int i = 1; i <= n; i++) {
        tmp = 0;
        for (int j = i; j <= n; j++) {
            if (tmp < a[j] + j - 1)
                tmp = a[j] + j - 1;
            flag[i][j] = tmp <= j;
        }
    }
    if (!flag[1][n]) {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) dp[i + 1][i] = 1;
    for (int l = 2; l <= n; l++)
        for (int i = 1, j = l; j <= n; i++, j++)
            if (flag[i][j])
                for (int k = i; k <= j; k++)
                    if (flag[i][k])
                        dp[i][j] = (dp[i][j] + dp[i + 1][k] * dp[k + 1][j]) % mod;
    printf("%lld\n", dp[2][n]);
    return 0;
}
