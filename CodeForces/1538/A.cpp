#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 110;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int p1, p2, ans;
    while (t--) {
        scanf("%d", &n);
        p1 = p2 = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (!p1 || a[i] < a[p1])
                p1 = i;
            if (!p2 || a[i] > a[p2])
                p2 = i;
        }
        if (p1 > p2)
            p1 ^= p2 ^= p1 ^= p2;
        ans = min(p1 + (n - p2 + 1), min(max(p1, p2), n - min(p1, p2) + 1));
        printf("%d\n", ans);
    }
    return 0;
}
