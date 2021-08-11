#include <cstdio>
using namespace std;

const int maxn = 110;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool ans;
    while (t--) {
        scanf("%d", &n);
        ans = true;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (a[i] < 0)
                ans = false;
        }
        if (!ans)
            printf("NO\n");
        else {
            printf("YES\n");
            printf("300\n");
            for (int i = 0; i < 300; i++) printf("%d ", i);
            printf("\n");
        }
    }
    return 0;
}
