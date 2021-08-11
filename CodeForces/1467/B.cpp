#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 300010;
bool p[maxn];
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int ans, m, tmp;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ans = m = 0;
        for (int i = 2; i < n; i++)
            p[i] = ((a[i] > a[i - 1] && a[i] > a[i + 1]) || (a[i] < a[i - 1] && a[i] < a[i + 1])),
            ans += p[i];
        p[1] = p[n] = false;
        for (int i = 2; i <= n; i++) {
            tmp = p[i - 1] + p[i] +
                  (i >= n - 1 ? 0
                              : p[i + 1] - ((a[i + 1] > a[i - 1] && a[i + 1] > a[i + 2]) ||
                                            (a[i + 1] < a[i - 1] && a[i + 1] < a[i + 2])));
            m = max(m, tmp);
        }
        for (int i = n - 1; i; i--) {
            tmp = p[i + 1] + p[i] +
                  (i <= 2 ? 0
                          : p[i - 1] - ((a[i - 1] > a[i - 2] && a[i - 1] > a[i + 1]) ||
                                        (a[i - 1] < a[i - 2] && a[i - 1] < a[i + 1])));
            m = max(m, tmp);
        }
        printf("%d\n", ans - m);
    }
    return 0;
}
