#include <cstdio>
using namespace std;

const int maxn = 500010;
const long long mod = 1000000007;
long long x[maxn], R[maxn];
int l[maxn], r[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld %lld", x + i, R + i), l[i] = r[i] = i;
    for (int i = 2; i <= n; i++)
        while (l[i] != 1 && x[i] - x[l[i] - 1] <= R[i]) {
            if (R[i] < R[l[i] - 1] + x[l[i] - 1] - x[i])
                R[i] = R[l[i] - 1] + x[l[i] - 1] - x[i];
            l[i] = l[l[i] - 1];
        }
    for (int i = n - 1; i; i--)
        while (r[i] != n && x[r[i] + 1] - x[i] <= R[i]) {
            if (l[i] > l[r[i] + 1])
                l[i] = l[r[i] + 1];
            r[i] = r[r[i] + 1];
        }
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans += (long long)i * (r[i] - l[i] + 1);
    printf("%lld\n", ans % mod);
    return 0;
}
