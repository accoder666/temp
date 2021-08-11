#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 60;
void dfs(int);
long long ans[maxn];
int a[maxn];
int n;

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int T;
    scanf("%d", &T);
    int cnt;
    while (T--) {
        scanf("%d", &n);
        cnt = 0;
        for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt += (a[i] != 0);
        printf("%d %lld", n, (long long)cnt * (cnt - 1) >> 1);
        memset(ans, 0, sizeof(ans));
        dfs(0);
        for (int i = 3; i <= n; i++) printf(" %lld", ans[i - 2]);
        printf("\n");
    }
    return 0;
}

void dfs(const int k) {
    ans[k]++;
    if (k == n - 2)
        return;
    for (int i = 1; i <= n; i++)
        if (a[i] > 1)
            a[i]--, dfs(k + 1), a[i]++;
    return;
}
