#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int l, r;
    long long ans;
    while (t--) {
        scanf("%d %d", &l, &r);
        ans = 0;
        for (long long i = 1; i <= r; i *= 10) ans += (r / i) - (l / i);
        printf("%lld\n", ans);
    }
    return 0;
}
