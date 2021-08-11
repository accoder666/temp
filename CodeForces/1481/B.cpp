#include <cstdio>
using namespace std;

const int maxn = 110;
int h[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k;
    int p;
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", h + i);
        while (k--) {
            p = n;
            for (int i = 1; i < n; i++)
                if (h[i] < h[i + 1]) {
                    p = i, h[i]++;
                    break;
                }
            if (p == n) {
                p = -1;
                break;
            }
        }
        printf("%d\n", p);
    }
    return 0;
}
