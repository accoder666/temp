#include <cstdio>
using namespace std;

int main() {
    int t, n, k, ans;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        ans = n - k;
        if (ans < 0)
            ans = -ans;
        if (!ans) {
            printf("0\n");
            continue;
        }
        if (n >= k)
            ans = (n + k) & 1;
        else if (ans > k - n)
            ans = k - n;
        printf("%d\n", ans);
    }
    return 0;
}
