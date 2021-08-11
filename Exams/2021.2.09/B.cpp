#include <cstdio>
using namespace std;

int main() {
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
    int n, m;
    scanf("%d %d %*d", &n, &m);
    long long ans = 0, a, b;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%lld %lld", &a, &b), ans += (a > b ? a : b);
    printf("%lld\n", ans);
    return 0;
}
