#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 510;
int a[maxn], tmp[maxn];
int M[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, x, ans, tmpans;
    while (t--) {
        ans = 0;
        scanf("%d %d", &n, &x);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        ans = -1;
        for (int i = 1; i <= n; i++)
            if (a[i] >= x) {
                for (int j = 1; j <= n; j++) tmp[j] = a[j];
                tmp[i] = x;
                sort(tmp + 1, tmp + n + 1);
                tmpans = 0;
                for (int j = 1; j <= n; j++)
                    if (a[j] != tmp[j]) {
                        if (j != i && a[j] < tmp[j]) {
                            tmpans = -1;
                            break;
                        } else
                            tmpans++;
                    }
                ans = max(ans, tmpans - 1);
            }
        printf("%d\n", ans);
    }
    return 0;
}
