#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    long long l, r, m;
    long long a, n, d, b, c;
    while (t--) {
        scanf("%lld %lld %lld", &l, &r, &m);
        a = n = d = b = c = 0;
        for (a = r; a >= l; a--) {
            d = 0, n = m / a;
            if (!n) {
                n = 1;
                while (a * n - m < r - l) n++;
                d = a * n - m;
                b = l, c = l + d;
            } else {
                d = m - a * n;
                b = r, c = r - d;
            }
            if ((l <= a && a <= r) && (l <= b && b <= r) && (l <= c && c <= r) && (a * n + b - c == m))
                break;
        }
        printf("%lld %lld %lld\n", a, b, c);
    }
    return 0;
}
