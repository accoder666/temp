#include <cstdio>
using namespace std;

int main() {
    int t, x;
    scanf("%d", &t);
    int ans, tmp1, tmp2;
    while (t--) {
        scanf("%d", &x);
        if (x == 1) {
            printf("1\n");
            continue;
        }
        ans = 1;
        while ((ans + 1) * (ans - 2) / 2 + 1 <= x) ans++;
        ans--;
        tmp1 = (ans + 1) * (ans - 2) / 2 + 1;
        tmp2 = (ans + 2) * (ans - 1) / 2 + 1;
        if (x == tmp1)
            ans--;
        else if (x == tmp2 - 1)
            ans++;
        printf("%d\n", ans);
    }
    return 0;
}
