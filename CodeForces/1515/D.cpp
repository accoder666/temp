#include <cstdio>
using namespace std;

const int maxn = 200010;
int c[maxn], b[2][maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, l, r;
    int ans, val, tmp, tmpp;
    while (t--) {
        scanf("%d %d %d", &n, &l, &r);
        ans = (n >> 1), val = (l > r ? l - r : r - l) >> 1;
        for (int i = 1; i <= n; i++) scanf("%d", c + i), b[0][i] = b[1][i] = 0;
        for (int i = 1; i <= l; i++) b[0][c[i]]++;
        for (int i = l + 1; i <= n; i++) b[1][c[i]]++;
        for (int i = 1; i <= n; i++) {
            tmp = (b[0][i] < b[1][i] ? b[0][i] : b[1][i]);
            tmpp = (b[0][i] > b[1][i] ? b[0][i] : b[1][i]) - tmp;
            ans -= tmp;
            if ((l < r && b[0][i] < b[1][i]) || (l > r && b[0][i] > b[1][i]))
                val -= tmpp >> 1;
        }
        ans += (val > 0 ? val : 0);
        printf("%d\n", ans);
    }
    return 0;
}
