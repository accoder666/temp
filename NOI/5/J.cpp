#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 510, maxm = 1000000;
const long long mod = 1000000007;
long long fac[2][maxm + 10];
struct node {
    int ls, rs, size;
};
node t[maxn];
stack<int> S;
int h[maxn];
void dfs(const int&, const int&);
long long dp[maxn][maxn];
int k;

int main() {
    int n;
    scanf("%d %d", &n, &k);
    fac[0][0] = fac[1][0] = 1;
    for (int i = 1; i <= maxm; i++) fac[0][i] = (long long)i * fac[0][i - 1] % mod;
    fac[1][maxm] = 1;
    long long base = fac[0][maxm], e = mod - 2;
    while (e) {
        if (e & 1ll)
            fac[1][maxm] = fac[1][maxm] * base % mod;
        e >>= 1ll, base = base * base % mod;
    }
    for (int i = maxm - 1; i; i--) fac[1][i] = fac[1][i + 1] * ((long long)i + 1) % mod;
    int last;
    for (int i = 1; i <= n; i++) {
        scanf("%d", h + i);
        last = 0;
        while (!S.empty() && h[S.top()] > h[i]) last = S.top(), S.pop();
        if (!S.empty())
            t[S.top()].rs = i;
        if (last)
            t[i].ls = last;
        S.push(i);
    }
    while (!S.empty()) last = S.top(), S.pop();
    dfs(last, 0);
    printf("%lld\n", dp[last][k]);
    return 0;
}

inline long long C(const int& n, const int& m) { return fac[0][n] * (fac[1][m] * fac[1][n - m] % mod) % mod; }

void dfs(const int& u, const int& val) {
    dp[u][0] = t[u].size = 1;
    if (t[u].ls) {
        dfs(t[u].ls, h[u]);
        t[u].size += t[t[u].ls].size;
        for (int i = min(t[u].size, k); i >= 0; i--)
            for (int j = 1; j <= min(t[t[u].ls].size, i); j++)
                dp[u][i] = (dp[u][i] + dp[u][i - j] * dp[t[u].ls][j] % mod) % mod;
    }
    if (t[u].rs) {
        dfs(t[u].rs, h[u]);
        t[u].size += t[t[u].rs].size;
        for (int i = min(t[u].size, k); i >= 0; i--)
            for (int j = 1; j <= min(t[t[u].rs].size, i); j++)
                dp[u][i] = (dp[u][i] + dp[u][i - j] * dp[t[u].rs][j] % mod) % mod;
    }
    for (int i = min(t[u].size, k); i >= 0; i--)
        for (int j = 1; j <= min(h[u] - val, i); j++)
            dp[u][i] = (dp[u][i] + ((dp[u][i - j] * fac[0][j] % mod) * C(h[u] - val, j) % mod) *
                                       C(t[u].size - i + j, j) % mod) %
                       mod;
    return;
}
