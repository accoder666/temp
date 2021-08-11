#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
int b[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, a, ans;
    while (t--) {
        scanf("%d", &n);
        memset(b, 0, sizeof(b));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            b[a]++;
        }
        ans = 0;
        for (int i = 1; i <= n; i++)
            if (ans < b[i])
                ans = b[i];
        printf("%d\n", ans);
    }
    return 0;
}
