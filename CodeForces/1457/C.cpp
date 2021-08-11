#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long long sum[maxn];
char S[maxn];

int main() {
    int t;
    scanf("%d", &t);
    long long n, p, k, x, y, ans;
    while (t--) {
        scanf("%lld %lld %lld", &n, &p, &k);
        scanf("%s", S + 1);
        scanf("%lld %lld", &x, &y);
        for (int i = n - k + 1; i <= n; i++) sum[i] = (S[i] == '0') * x;
        for (int i = n - k; i; i--) sum[i] = sum[i + k] + (S[i] == '0') * x;
        ans = INT_MAX;
        for (int i = p; i <= n; i++) ans = min(ans, sum[i] + (i - p) * y);
        printf("%lld\n", ans);
    }
    return 0;
}
