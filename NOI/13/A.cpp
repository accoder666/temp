#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long ans = n * k;
    for (long long l = 1, r = 1; l <= n; l = r + 1, r = k / l ? min(k / (k / l), n) : n)
        ans -= (k / l) * (l + r) * (r - l + 1) >> 1ll;
    printf("%lld\n", ans);
    return 0;
}
