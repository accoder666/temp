#include <cstdio>
using namespace std;

int main() {
    long long n;
    scanf("%lld", &n);
    long long ans = n, c;
    for (long long i = 2; i * i <= n; i++)
        if (!(n % i)) {
            c = 0;
            while (!(n % i)) n /= i, c++;
            ans = ans / i * (c * i - c + i);
        }
    if (n != 1)
        ans = ans / n * ((n << 1ll) - 1ll);
    printf("%lld\n", ans);
    return 0;
}
