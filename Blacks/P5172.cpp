#include <cmath>
#include <cstdio>
using namespace std;

long long f(const long long&, const long long&, const long long&, const long long&);
long long r;

int main() {
    int t;
    scanf("%d", &t);
    long long n;
    while (t--) {
        scanf("%lld %lld", &n, &r);
        if (floorl(sqrtl((long double)r)) * floorl(sqrtl((long double)r)) == r)
            printf("%lld\n", (long long)floorl(sqrtl((long double)r)) & 1 ? -(n & 1ll) : n);
        else
            printf("%lld\n", n + (f(1, 0, 2, n) << 2ll) - (f(1, 0, 1, n) << 1ll));
    }
    return 0;
}

long long gcd(const long long& x, const long long& y) {
    if (x < y)
        return gcd(y, x);
    if (!y)
        return x;
    if (y < 0)
        return gcd(x, -y);
    return gcd(y, x % y);
}

long long f(const long long& a, const long long& b, const long long& c, const long long& n) {
    if (!n)
        return 0;
    long long g = gcd(gcd(a, b), c);
    if (g != 1)
        return f(a / g, b / g, c / g, n);
    auto v = (long long)floorl((a * sqrtl((long double)r) + b) / c);
    if (v)
        return (v * n * (n + 1) >> 1ll) + f(a, b - c * v, c, n);
    auto tmp = (long long)floorl((a * sqrtl((long double)r) + b) * n / c);
    return n * tmp - f(a * c, -b * c, a * a * r - b * b, tmp);
}
