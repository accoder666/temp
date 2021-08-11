#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long long s[maxn], c[maxn], ans[maxn];
int t;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    long long v;
    s[++t] = n;
    while (q--) {
        scanf("%lld", &v);
        while (t && s[t] >= v) t--;
        s[++t] = v;
    }
    int p;
    long long x, y;
    c[t] = 1;
    for (int i = t; i; i--) {
        p = i - 1, x = s[i], y = c[i];
        while (p) {
            c[p] += y * (x / s[p]);
            x %= s[p];
            p = upper_bound(s + 1, s + t + 1, x) - s;
            if (p == 1)
                ans[1] += y, ans[x + 1] -= y;
            p--;
        }
    }
    for (int i = 1; i <= s[1]; i++) printf("%lld\n", (ans[i] += ans[i - 1]) + c[1]);
    for (int i = s[1] + 1; i <= n; i++) printf("0\n");
    return 0;
}
