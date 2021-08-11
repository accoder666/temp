#include <cstdio>
using namespace std;

inline int min(const int&, const int&);

int main() {
    int t, x1, y1, z1, x2, y2, z2, ans, cnt;
    scanf("%d", &t);
    while (t--) {
        ans = 0;
        scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
        cnt = min(z1, y2);
        ans += cnt << 1, z1 -= cnt, y2 -= cnt;
        if (z1) {
            cnt = min(z1, z2);
            z1 -= cnt, z2 -= cnt;
            if (z1) {
                cnt = min(z1, x1);
                z1 -= cnt, x1 -= cnt;
            }
        }
        if (z2) {
            cnt = min(x1, z2);
            x1 -= cnt, z2 -= cnt;
            if (z2) {
                cnt = min(y1, z2);
                ans -= cnt << 1, z2 -= cnt, y1 -= cnt;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

inline int min(const int& a, const int& b) { return a < b ? a : b; }
