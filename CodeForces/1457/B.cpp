#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int c[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k, p, ans, tmp;
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", c + i);
        ans = INT_MAX;
        for (int i = 1; i <= 100; i++) {
            tmp = 0;
            for (int j = 1; j <= n; j++)
                if (c[j] != i)
                    tmp++, j += k - 1;
            if (tmp < ans)
                ans = tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}
