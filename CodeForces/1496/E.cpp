#include <cstdio>
using namespace std;

const int maxn = 510;
bool f[maxn][maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m;
    char ch;
    while (t--) {
        scanf("%d %d", &n, &m);
        ch = getchar();
        for (int i = 1; i <= n; i++) {
            while (ch != 'X' && ch != '.') ch = getchar();
            for (int j = 1; j <= m; j++) f[i][j] = (ch == 'X'), ch = getchar();
        }
        for (int i = 1 + (n % 3 == 0); i <= n;) {
            for (int j = 1; j <= m; j++) f[i][j] = true;
            i += 3;
            if (i <= n) {
                if (m == 1 || (!f[i - 1][2] && !f[i - 2][2]))
                    f[i - 1][1] = f[i - 2][1] = true;
                else
                    f[i - 1][2] = f[i - 2][2] = true;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) putchar(f[i][j] ? 'X' : '.');
            putchar('\n');
        }
    }
    return 0;
}
