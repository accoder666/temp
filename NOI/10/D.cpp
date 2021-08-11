#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
struct node {
    int s, e, p;
    inline bool operator<(const node& rhs) const { return p < rhs.p; }
};
node t[maxn];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) scanf("%d %d %d", &t[i].s, &t[i].e, &t[i].p);
    sort(t + 1, t + n + 1);
    int x, a, b, c, k;
    long long ans, pre = 1;
    int cnt;
    while (n--) {
        scanf("%d %d %d %d", &x, &a, &b, &c);
        k = (int)(((long long)a * pre + b) % c + 1);
        ans = cnt = 0;
        for (int i = 1; i <= m; i++)
            if (t[i].s <= x && x <= t[i].e) {
                ans += t[i].p;
                if (++cnt == k)
                    break;
            }
        printf("%lld\n", pre = ans);
    }
    return 0;
}
