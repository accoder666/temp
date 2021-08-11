#include <cstdio>
using namespace std;

const int maxn = 110;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k, tmp;
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i < n && k; i++) {
            tmp = (a[i] > k ? k : a[i]);
            a[n] += tmp, a[i] -= tmp, k -= tmp;
        }
        for (int i = 1; i <= n; i++) printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}
