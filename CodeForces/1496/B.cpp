#include <cstdio>
#include <unordered_set>
using namespace std;

const int maxn = 100010;
unordered_set<int> S;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k;
    int ans;
    int p, m, val;
    while (t--) {
        scanf("%d %d", &n, &k);
        ans = n, m = 0;
        S.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            S.insert(a[i]);
            if (a[i] > m)
                m = a[i];
        }
        p = 0;
        while (S.count(p)) p++;
        if (p == n) {
            printf("%d\n", n + k);
            continue;
        }
        while (k--) {
            val = ((p + m) >> 1) + ((p + m) & 1);
            if (S.count(val))
                break;
            S.insert(val);
            while (S.count(p)) p++;
            if (val > m)
                m = val;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
