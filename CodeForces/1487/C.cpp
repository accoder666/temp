#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
int ans[maxn][maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int u, cnt;
    while (t--) {
        scanf("%d", &n);
        cnt = (n - 1) * n >> 1;
        memset(ans, 0, sizeof(ans));
        for (int d = 0; cnt != (!(n & 1)) * (n >> 1); d++)
            for (int p = 1; cnt != (!(n & 1)) * (n >> 1) && p <= d + 1; p++) {
                u = p;
                do {
                    if (u <= (u + d) % n) {
                        if (!ans[u][(u + d) % n + 1])
                            ans[u][(u + d) % n + 1] = 1, cnt--;
                    } else {
                        if (!ans[(u + d) % n + 1][u])
                            ans[(u + d) % n + 1][u] = -1, cnt--;
                    }
                    u = (u + d) % n + 1;
                } while (u != p);
            }
        for (int i = 1; i < n; i++)
            for (int j = i + 1; j <= n; j++) printf("%d ", ans[i][j]);
        printf("\n");
    }
    return 0;
}
