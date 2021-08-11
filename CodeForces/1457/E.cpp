#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 500010;
priority_queue<long long> Q;
long long c[maxn];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", c + i);
    sort(c + 1, c + n + 1);
    for (int i = 0; i <= k; i++) Q.push(0);
    long long ans = 0, x;
    for (int i = n; i; i--) x = Q.top(), ans += x, Q.pop(), Q.push(x + c[i]);
    printf("%lld\n", ans);
    return 0;
}
