#include <cstdio>
using namespace std;

long long solve(const long long&, const long long&, const long long&, const long long&);

int main() {
    int t;
    scanf("%d", &t);
    long long ans;
    long long a, b, p, q;
    long long l, r, mid;
    while (t--) {
        scanf("%lld %lld %lld %lld", &a, &b, &p, &q);
        ans = solve(n, a, b, c);
        printf("%lld\n", ans);
    }
    return 0;
}

long long solve(const long long& n, const long long& a, const long long& b, const long long& c) {
    long long S0 = n + 1, S1 = n * (n + 1) >> 1;
    long long A = a / c, B = b / c;
    if (!a)
        return B * S0;
    if (a < c && b < c) {
        long long m = (a * n + b) / c;
        long long t = solve((a * n + b) / c - 1, c, c - b - 1, a);
        return n * m - t;
    }
    long long t = solve(n, a % c, b % c, c);
    return A * S1 + B * S0 + t;
}
