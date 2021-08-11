#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int l, r, mid, ans;
    while (t--) {
        scanf("%d", &n);
        l = 0, r = n;
        while (l <= r) {
            mid = (l + r) >> 1;
            if ((((long long)mid * mid + mid) << 1) + 1 <= n)
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
