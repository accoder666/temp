#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 110;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int cnt;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        sort(a + 1, a + n + 1);
        cnt = 0;
        while (cnt < n && a[cnt + 1] == a[1]) cnt++;
        printf("%d\n", n - cnt);
    }
    return 0;
}
