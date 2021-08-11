#include <cstdio>
using namespace std;

const int maxn = 1010;
char f[2][maxn];

int main() {
    int T;
    scanf("%d", &T);
    int n, m, cur;
    while (T--) {
        cur = 0;
        scanf("%d %d", &n, &m);
        scanf("%s", f[cur] + 1);
        if (m > n)
            m = n;
        f[0][0] = f[0][n + 1] = f[1][0] = f[1][n + 1] = '\0';
        for (int i = 1; i <= m; i++) {
            cur ^= 1;
            for (int j = 1; j <= n; j++)
                if ((f[cur ^ 1][j - 1] == '1') + (f[cur ^ 1][j + 1] == '1') == 1 || f[cur ^ 1][j] == '1')
                    f[cur][j] = '1';
                else
                    f[cur][j] = '0';
        }
        printf("%s\n", f[cur] + 1);
    }
    return 0;
}
