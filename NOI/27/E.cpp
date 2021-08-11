// fixme

#include <cstdio>
using namespace std;

const int maxn = 16;
int p[maxn + 10];
int cnt[(1 << maxn) + 10];

int main() {
    int n, g, l, q;
    scanf("%d %d %d", &n, &g, &l);
    scanf("%d", &q);
    if (l % g) {
        while (q--) printf("0\n");
        return 0;
    }
    n /= g, l /= g;
    int c = 0;
    for (int i = 1; i * i <= l && i <= n; i++)
        if (!(l % i)) {
            p[++c] += i;
            if (l != i * i)
                p[++c] = l / i;
        }
    int x;
    while (q--) {
        scanf("%d", &x);
        if (x % g || x > n) {
            printf("0\n");
            continue;
        }
        x /= g;
    }
    return 0;
}
