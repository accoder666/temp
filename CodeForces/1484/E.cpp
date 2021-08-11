#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 300010;
int h[maxn];
long long b[maxn];
int s[maxn], t;
long long v[maxn], p[maxn];
long long dp[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", h + i);
    for (int i = 1; i <= n; i++) scanf("%lld", b + i);
    long long val;
    p[0] = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        val = dp[i - 1];
        while (t && h[s[t]] > h[i]) {
            if (val < v[t])
                val = v[t];
            t--;
        }
        s[++t] = i, v[t] = val;
        dp[i] = p[t - 1] > v[t] + b[i] ? p[t - 1] : v[t] + b[i];
        p[t] = dp[i];
    }
    printf("%lld\n", dp[n]);
    return 0;
}
