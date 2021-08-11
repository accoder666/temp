#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1010;
bool f[maxn][maxn], val[maxn][2];
int to[maxn][2];

int main() {
    int t;
    scanf("%d", &t);
    int n, m;
    char ch;
    bool flag;
    while (t--) {
        scanf("%d %d", &n, &m);
        ch = getchar();
        for (int i = 1; i <= n; i++) {
            while (ch != 'a' && ch != 'b' && ch != '*') ch = getchar();
            for (int j = 1; j <= n; j++) {
                if (i != j)
                    f[i][j] = (ch == 'a');
                ch = getchar();
            }
        }
        flag = false;
        memset(f, false, sizeof(bool) * (n + 5));
        for (int i = 1; i <= n && !flag; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && f[i][j] == f[j][i]) {
                    printf("YES\n");
                    for (int k = 0; k <= m; k++) printf("%d ", (k & 1) ? i : j);
                    printf("\n");
                    flag = true;
                    break;
                } else if (!f[i][j])
                    val[i][0] = true, to[i][0] = j;
                else
                    val[i][1] = true, to[i][1] = j;
        if (flag)
            continue;
        if (m & 1) {
            printf("YES\n");
            for (int i = 0; i <= m; i++) printf("%d ", (i & 1) + 1);
            printf("\n");
        } else if (m & 2) {
            printf("NO\n");
        } else {
            for (int i = 1; i <= n; i++)
                if (val[i][0] && val[i][1]) {
                    printf("YES\n%d ", i);
                    for (int j = 0; j < m >> 1; j++) printf("%d ", (j & 1) ? i : to[i][0]);
                    for (int j = 0; j < m >> 1; j++) printf("%d ", (j & 1) ? i : to[i][1]);
                    printf("\n");
                    flag = true;
                    break;
                }
            if (!flag)
                printf("NO\n");
        }
    }
    return 0;
}
