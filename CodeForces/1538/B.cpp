#include <cstdio>
using namespace std;

const int maxn = 200010;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int sum, ans;
    while (t--) {
        scanf("%d", &n);
        sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            sum += a[i];
        }
        if (sum % n)
            printf("-1\n");
        else {
            ans = 0, sum /= n;
            for (int i = 1; i <= n; i++)
                if (a[i] > sum)
                    ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}
