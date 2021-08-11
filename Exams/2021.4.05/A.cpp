#include <cstdio>
using namespace std;

const int maxn = 1010;
struct circle {
    int a, b, c;
};
circle ans[maxn * maxn];

int main() {
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int m = 0;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++) {
            ans[++m] = { i, j, n + (i + j >= n) * n - i - j };
            if (ans[m].c <= ans[m].b)
                m--;
        }
    if ((n * (n - 1) >> 1) - 3 * m >= n) {
        printf("No\n");
        return 0;
    }
    printf("Yes\n");
    printf("%d\n", m);
    for (int i = 1; i <= m; i++) printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
    return 0;
}
