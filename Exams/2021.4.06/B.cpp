#include <cstdio>
using namespace std;

const long long mod = 998244353;
const int maxn = 60;
struct edge {
    int to, nxt;
};
edge G[maxn];
int head[maxn], cnt;
long long dp[maxn][maxn][2];
void dfs(int);
long long C[maxn][maxn];
long long pow[maxn];
long long f[maxn], g[maxn];

int main() {
    freopen("kaisou.in", "r", stdin);
    freopen("kaisou.out", "w", stdout);
    int n, k;
    scanf("%d %d", &n, &k);
    int fa;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &fa), fa++;
        G[++cnt] = { i, head[fa] }, head[fa] = cnt;
    }
    dfs(1);
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if (C[i][j] >= mod)
                C[i][j] -= mod;
        }
    }
    pow[0] = 1;
    for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * n % mod;
    for (int i = 0; i < n - 1; i++) g[i] = dp[1][n - i][1] * pow[n - i - 2] % mod;
    g[n - 1] = 1;
    for (int i = n; i >= 0; i--) {
        f[i] = g[i];
        for (int j = i + 1; j <= n; j++) {
            f[i] = f[i] - f[j] * C[j][i] % mod;
            if (f[i] < 0)
                f[i] += mod;
        }
    }
    long long ans = 0;
    for (int i = n - 1 - k; i < n; i++) ans += f[i];
    printf("%lld\n", ans % mod);
    return 0;
}

int siz[maxn];
long long tmp[maxn][maxn][2];
void dfs(const int u) {
    dp[u][1][0] = dp[u][1][1] = 1, siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt) {
        dfs(G[i].to);
        for (int j = siz[u]; j; j--)
            for (int k = siz[G[i].to]; k; k--) {
                tmp[u][j + k][0] = (tmp[u][j + k][0] + dp[u][j][0] * dp[G[i].to][k][1]) % mod;
                tmp[u][j + k][1] = (tmp[u][j + k][1] + dp[u][j][1] * dp[G[i].to][k][1]) % mod;
                tmp[u][j + k - 1][0] = (tmp[u][j + k - 1][0] + dp[u][j][0] * dp[G[i].to][k][0]) % mod;
                tmp[u][j + k - 1][1] = (tmp[u][j + k - 1][1] + dp[u][j][1] * dp[G[i].to][k][0] +
                                        dp[u][j][0] * dp[G[i].to][k][1]) %
                                       mod;
            }
        siz[u] += siz[G[i].to];
        for (int j = 1; j <= siz[u]; j++) {
            dp[u][j][0] = tmp[u][j][0], dp[u][j][1] = tmp[u][j][1];
            tmp[u][j][0] = tmp[u][j][1] = 0;
        }
    }
    return;
}
