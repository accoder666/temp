#include <cstdio>
using namespace std;

inline long long sum(long long);

int main() {
    freopen("zuiqianyande.in", "r", stdin);
    freopen("zuiqianyande.out", "w", stdout);
    long long n;
    scanf("%lld", &n);
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        if ((n / l) & 1)
            ans ^= (sum(l - 1) ^ sum(r));
    }
    printf("%lld\n", ans);
    return 0;
}

inline long long sum(const long long x) {
    if (!x)
        return 0;
    long long ret = (x % 4 == 1 || x % 4 == 2);
    if (!(x & 1))
        ret += x;
    return ret;
}
