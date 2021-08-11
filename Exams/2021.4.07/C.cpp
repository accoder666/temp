#pragma GCC optimize("Ofast")

#include <cstdio>
#include <cstring>
using namespace std;

const int d[5] = { 1, 2, 3, 5, 7 };
const int lcm = 10857;
const int mod = 9973;
int dp[2][lcm + 10];

int main() {
    //    freopen("c.in", "r", stdin);
    //    freopen("c.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int cur = 0;
    dp[cur][0] = 1;
    int tmp;
    while (n--) {
        cur ^= 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        tmp = 0;
        for (int i = 0; i < lcm; i++) {
            for (int val : d) {
                if (!n && (val == 2 || val == 5))
                    continue;
                tmp += val;
                if (tmp >= lcm)
                    tmp -= lcm;
                dp[cur][tmp] += dp[cur ^ 1][i];
                if (dp[cur][tmp] >= mod)
                    dp[cur][tmp] -= mod;
                tmp -= val;
                if (tmp < 0)
                    tmp += lcm;
            }
            tmp += 10;
            if (tmp >= lcm)
                tmp -= lcm;
        }
    }
    int ans = 0;
    for (int i = 0; i < lcm; i++)
        if ((i % 3) && (i % 7) && (i % 11) && (i % 47))
            ans += dp[cur][i];
    printf("%d\n", ans % mod);
    return 0;
}
