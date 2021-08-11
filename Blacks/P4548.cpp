#include <cstdio>
using namespace std;

const int mod = 10000;
const int maxn = 100010;
int a[maxn], nxt[maxn];
int power[maxn];

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    int m;
    int p, ans;
    int lim = 0;
    power[0] = 1;
    while (t--) {
        scanf("%d", &m);
        while (lim < m) power[lim + 1] = power[lim] * n % mod, lim++;
        p = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", a + i);
            if (i == 1)
                continue;
            while (p && a[p + 1] != a[i]) p = nxt[p];
            if (a[p + 1] == a[i])
                p++;
            nxt[i] = p;
        }
        ans = 0;
        for (int i = m; i; i = nxt[i]) ans += power[i];
        printf("%04d\n", ans % mod);
    }
    return 0;
}
