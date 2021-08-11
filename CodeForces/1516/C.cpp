#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110, maxv = 200010;
bool dp[2][maxv];
int a[maxn];

int main() {
    int n;
    scanf("%d", &n);
    int s = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), s += a[i];
    int cur = 0;
    dp[cur][0] = true;
    for (int i = 1; i <= n; i++) {
        cur ^= 1;
        memset(dp[cur], false, sizeof(dp[cur]));
        for (int j = 0; j <= s; j++) dp[cur][j] |= dp[cur ^ 1][j];
        for (int j = a[i]; j <= s; j++) dp[cur][j] |= dp[cur ^ 1][j - a[i]];
    }
    if ((s & 1) || !dp[cur][s >> 1]) {
        printf("0\n");
        return 0;
    }
    bool flag;
    while (true) {
        flag = true;
        for (int i = 1; i <= n; i++)
            if (a[i] & 1) {
                flag = false;
                break;
            }
        if (!flag)
            break;
        for (int i = 1; i <= n; i++) a[i] >>= 1;
    }
    for (int i = 1; i <= n; i++)
        if (a[i] & 1) {
            printf("1\n%d\n", i);
            break;
        }
    return 0;
}
