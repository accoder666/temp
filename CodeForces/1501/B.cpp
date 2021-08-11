#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 200010;
int v[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, a;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) v[i] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            v[i]++, v[max(0, i - a)]--;
        }
        for (int i = n - 1; i; i--) v[i] += v[i + 1];
        for (int i = 1; i <= n; i++) printf("%d ", v[i] != 0);
        printf("\n");
    }
    return 0;
}
