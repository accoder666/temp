#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long x, a, minv, maxv;
    while (t--) {
        scanf("%d %lld", &n, &x);
        minv = maxv = 0;
        for (int i = 1; i <= n; i++) scanf("%lld", &a), minv += a, maxv += ceil(a * 1.0 / x);
        minv = ceil(minv * 1.0 / x);
        printf("%lld %lld\n", minv, maxv);
    }
    return 0;
}
