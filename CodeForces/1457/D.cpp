#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 100;
int a[maxn], s[maxn];

int main() {
    int n;
    scanf("%d", &n);
    if (n > 60) {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) scanf("%d", a + i), s[i] = s[i - 1] ^ a[i];
    a[n + 1] = INT_MAX;
    int ans = INT_MAX;
    for (int l = 1; l < n; l++)
        for (int r = l + 1; r <= n; r++)
            for (int k = l; k < r; k++)
                if ((s[k] ^ s[l - 1]) > (s[r] ^ s[k]))
                    ans = min(ans, r - l - 1);
    printf("%d\n", ans == INT_MAX ? -1 : ans);
    return 0;
}
