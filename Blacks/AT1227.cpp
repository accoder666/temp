#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 3010;
struct point {
    int x, y, c, p;
    inline bool operator<(const point& rhs) const { return (long long)x * rhs.y < (long long)y * rhs.x; }
};
point a[maxn], p[maxn];
int cnt[2][3];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].c);
    long long ans = 0;
    int c;
    for (int i = 1; i <= n; i++) {
        cnt[0][0] = cnt[0][1] = cnt[0][2] = cnt[1][0] = cnt[1][1] = cnt[1][2] = 0;
        c = 0;
        for (int j = 1; j <= n; j++)
            if (i != j) {
                p[++c] = { a[j].x - a[i].x, a[j].y - a[i].y, (a[j].c - a[i].c + 3) % 3, 0 };
                if ((p[c].p = p[c].y < 0 || (p[c].y == 0 && p[c].x < 0)))
                    p[c].x = -p[c].x, p[c].y = -p[c].y;
                cnt[p[c].p][p[c].c]++;
            }
        sort(p + 1, p + n);
        for (int j = 1; j < n; j++) {
            cnt[p[j].p][p[j].c]--;
            ans += (long long)cnt[0][1] * cnt[0][2] * cnt[1][(p[j].c + 1) % 3] * cnt[1][(p[j].c + 2) % 3];
            ans += (long long)cnt[1][1] * cnt[1][2] * cnt[0][(p[j].c + 1) % 3] * cnt[0][(p[j].c + 2) % 3];
            cnt[p[j].p ^= 1][p[j].c]++;
        }
    }
    printf("%lld\n", ans >> 2);
    return 0;
}
