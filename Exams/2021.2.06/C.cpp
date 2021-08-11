#include <cstdio>
using namespace std;

const int maxn = 300;
long double dp[maxn + 10][maxn + 10], C[maxn + 10][maxn + 10];
int s[maxn + 10], c;
int a[maxn + 10];

int main() {
    freopen("unlock.in", "r", stdin);
    freopen("unlock.out", "w", stdout);
    C[0][0] = 1;
    for (int i = 1; i <= maxn; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    int t;
    scanf("%d", &t);
    int n, k;
    int u, tmp;
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        c = 0;
        for (int i = 1; i <= n; i++)
            if (a[i]) {
                s[++c] = 1;
                u = a[i], a[i] = 0;
                while (a[u]) s[c]++, tmp = u, u = a[u], a[tmp] = 0;
            }
        dp[0][0] = 1;
        for (int i = 1; i <= c; i++)
            for (int j = 1; j <= k; j++) {
                dp[i][j] = 0;
                for (int d = 1; d <= j && d <= s[i]; d++) dp[i][j] += dp[i - 1][j - d] * C[s[i]][d];
            }
        printf("%.10Lf\n", dp[c][k] / C[n][k]);
    }
    return 0;
}
