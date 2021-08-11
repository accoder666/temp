#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10;
int v[maxn + 10], a[maxn + 10];
int dp[(1 << maxn) + 10];

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", v + i);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 0;
    memset(dp, 0xfe, sizeof(dp));
    dp[0] = 0;
    int l, r;
    bool flag;
    for (int i = 1; i < 1 << n; i++) {
        for (l = 1; l <= n; l = r + 1)
            if (i & (1 << (l - 1))) {
                r = l;
                while (r < n && i & (1 << r)) r++;
                for (int x = l; x <= r; x++)
                    for (int y = x; y <= r; y++) {
                        flag = true;
                        for (int p = x; p < y; p++) flag &= (a[p] - a[p + 1] == 1 || a[p] - a[p + 1] == -1);
                        for (int p = x + 1; p < y; p++) flag &= (a[p] >= a[p + 1] || a[p] >= a[p - 1]);
                        if (flag)
                            dp[i] = max(dp[i], dp[i ^ ((1 << y) - (1 << (x - 1)))] + v[y - x + 1]);
                    }
            } else
                r = l;
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}
