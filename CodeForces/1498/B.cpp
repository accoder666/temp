#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010, maxl = 25;
int cnt[maxl], l[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, W, w;
    int ans;
    while (t--) {
        scanf("%d %d", &n, &W);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) scanf("%d", &w), cnt[__builtin_ctz(w)]++;
        for (int i = 1; i <= n + 1; i++) l[i] = W;
        for (int i = maxl - 1; i >= 0; i--)
            for (int j = 1; cnt[i] && j <= n + 1; j++)
                while (cnt[i] && l[j] >= (1 << i)) l[j] -= (1 << i), cnt[i]--;
        ans = 0;
        while (l[ans + 1] != W) ans++;
        printf("%d\n", ans);
    }
    return 0;
}
