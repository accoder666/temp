#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    long long n, ans;
    while (t--) {
        scanf("%lld", &n);
        if (n % 2050)
            printf("-1\n");
        else {
            n /= 2050, ans = 0;
            while (n) ans += n % 10, n /= 10;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
