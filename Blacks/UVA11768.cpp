#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

long long exgcd(const long long&, const long long&, long long&, long long&);

int main() {
    int n;
    scanf("%d", &n);
    long double x1, y1, x2, y2;
    long long tx1, ty1, tx2, ty2;
    long long a, b, c, x, y, gcd, rep, l, r, p;
    while (n--) {
        scanf("%Lf %Lf %Lf %Lf", &x1, &y1, &x2, &y2);
        tx1 = x1 * 10, ty1 = y1 * 10, tx2 = x2 * 10, ty2 = y2 * 10;
        if (x1 == x2)
            if (tx1 % 10)
                printf("0\n");
            else
                printf("%lld\n", (int)floorl(max(y1, y2)) - (int)ceill(min(y1, y2)) + 1);
        else if (y1 == y2)
            if (ty1 % 10)
                printf("0\n");
            else
                printf("%lld\n", (int)floorl(max(x1, x2)) - (int)ceill(min(x1, x2)) + 1);
        else {
            a = (ty2 - ty1) * 10, b = (tx1 - tx2) * 10, c = tx1 * ty2 - tx2 * ty1;
            gcd = exgcd(a, b, x, y);
            if (c % gcd)
                printf("0\n");
            else {
                x = x * c / gcd;
                rep = abs(b / gcd);
                l = ceill(min(x1, x2)), r = floorl(max(x1, x2));
                if (l <= r) {
                    p = x + (l - x) / rep * rep;
                    if (p < l)
                        p += rep;
                    if (p > r)
                        printf("0\n");
                    else
                        printf("%lld\n", (r - p) / rep + 1);
                } else
                    printf("0\n");
            }
        }
    }
    return 0;
}

long long exgcd(const long long& a, const long long& b, long long& x, long long& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return g;
}
