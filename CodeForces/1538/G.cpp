#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int x, y, a, b;
    int l, r, mid, ans;
    int L, R;
    while (t--) {
        scanf("%d %d %d %d", &x, &y, &a, &b);
        if (a == b) {
            printf("%d\n", min(x / a, y / a));
            continue;
        }
        if (a < b) {
            a ^= b ^= a ^= b;
            x ^= y ^= x ^= y;
        }
        l = 0, r = (x + y) / (a + b), ans = 0;
        while (l <= r) {
            mid = (l + r) >> 1;
            L = (int)ceill(((long double)y - (long double)mid * a) / ((long double)b - a));
            R = (int)floorl(((long double)x - (long double)mid * b) / ((long double)a - b));
            L = max(L, 0), R = min(R, mid);
            if (L <= R)
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
