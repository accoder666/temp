#include <cstdio>
using namespace std;

long long gcd(const long long&, const long long&);

int main() {
    int t;
    scanf("%d", &t);
    long long n;
    long long x, sum, tmp;
    while (t--) {
        scanf("%lld", &n);
        x = n, sum = 0;
        while (n) sum += n % 10, n /= 10;
        while (gcd(x, sum) == 1) {
            tmp = x;
            while (tmp % 10 == 9) sum -= 9, tmp /= 10;
            x++, sum++;
        }
        printf("%lld\n", x);
    }
    return 0;
}

long long gcd(const long long& a, const long long& b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}
