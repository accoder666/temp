#include <cstdio>
using namespace std;

const long long mod = 1000000007;

int main() {
    int t;
    scanf("%d", &t);
    long long n, k, ans;
    while (t--) {
        scanf("%d %d", &n, &k);
        ans = 1;
        while (k) {
            if (k & 1)
                ans = ans * n % mod;
            n = n * n % mod, k >>= 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
