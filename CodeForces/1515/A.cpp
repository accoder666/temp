#include <cstdio>
using namespace std;

const int maxn = 110;
int w[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, x, sum, p;
    while (t--) {
        sum = p = 0;
        scanf("%d %d", &n, &x);
        for (int i = 1; i <= n; i++) {
            scanf("%d", w + i), sum += w[i];
            if (sum == x)
                p = i;
        }
        if (sum == x)
            printf("NO\n");
        else if (p) {
            printf("YES\n");
            for (int i = 1; i < p; i++) printf("%d ", w[i]);
            printf("%d %d", w[p + 1], w[p]);
            for (int i = p + 2; i <= n; i++) printf(" %d", w[i]);
            printf("\n");
        } else {
            printf("YES\n");
            for (int i = 1; i <= n; i++) printf("%d ", w[i]);
            printf("\n");
        }
    }
    return 0;
}
