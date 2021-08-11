#include <cstdio>
using namespace std;

const long long mod = 998244353;
const int maxn = 1000010;
long long dp[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = i << 1; j <= n; j += i) dp[j]++;
    long long ans = dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] += ans;
        if (dp[i] >= mod)
            dp[i] -= mod;
        ans += dp[i];
        if (ans >= mod)
            ans -= mod;
    }
    printf("%lld\n", dp[n]);
    return 0;
}
