#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 510, maxa = 10;
const int inv[7] = { 0, 1, 4, 5, 2, 3, 6 };
int c[maxa], val[maxa], cnt[maxn];
int a[maxn], dp[maxn][maxn][maxn];

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n + 1; i++) c[(a[i] - a[i - 1] + 7) % 7]++;
    int ans = 0;
    for (int i = 1; i <= 3; i++) {
        ans += min(c[i], c[7 - i]);
        if (c[i] > c[7 - i])
            val[i] = i, cnt[i] = c[i] - c[7 - i];
        else
            val[i] = 7 - i, cnt[i] = c[7 - i] - c[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    int c3;
    for (int i = 0; i <= cnt[1]; i++)
        for (int j = 0; j <= cnt[2]; j++)
            for (int k = 0; k <= cnt[3]; k++) {
                for (int c1 = 0; c1 < 7; c1++)
                    for (int c2 = 0; c2 < 7; c2++) {
                        c3 = (7 * 7 * 2 - c1 * val[1] - c2 * val[2]) * inv[val[3]] % 7;
                        if ((c1 || c2 || c3) && c1 <= i && c2 <= j && c3 <= k)
                            dp[i][j][k] = min(dp[i][j][k], dp[i - c1][j - c2][k - c3] + c1 + c2 + c3 - 1);
                    }
                if (i >= 7)
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 7][j][k] + 6);
                if (j >= 7)
                    dp[i][j][k] = min(dp[i][j][k], dp[i][j - 7][k] + 6);
                if (k >= 7)
                    dp[i][j][k] = min(dp[i][j][k], dp[i][j][k - 7] + 6);
            }
    printf("%d\n", ans + dp[cnt[1]][cnt[2]][cnt[3]]);
    return 0;
}
