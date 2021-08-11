#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int a[maxn], sorted[maxn];

int main() {
    int t, n;
    bool f;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), sorted[i] = a[i];
        sort(sorted + 1, sorted + n + 1);
        f = true;
        for (int i = 1; i <= n; i++)
            if (a[i] % sorted[1] && a[i] != sorted[i]) {
                printf("NO\n");
                f = false;
                break;
            }
        if (f)
            printf("YES\n");
    }
    return 0;
}
