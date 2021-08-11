#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 30;
void dfs1(const int&, const int&, const int&, const int&, const int&, const int&);
bool dfs2(const int&, const int&, const int&, const int&, const int&, const int&);
bool map[maxn][maxn], vis[maxn][maxn], v[maxn][maxn];

int main() {
    freopen("village.in", "r", stdin);
    freopen("village.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    char ch = getchar();
    for (int i = 1; i <= n; i++) {
        while (ch != '0' && ch != '1') ch = getchar();
        for (int j = 1; j <= m; j++) map[i][j] = (ch == '1'), ch = getchar();
    }
    bool flag;
    long long ans = 0;
    for (int x1 = 1; x1 <= n; x1++)
        for (int y1 = 1; y1 <= m; y1++)
            for (int x2 = x1; x2 <= n; x2++)
                for (int y2 = y1; y2 <= m; y2++) {
                    memset(vis, false, sizeof(vis));
                    memset(v, false, sizeof(v));
                    flag = false;
                    for (int x = x1; x <= x2; x++) {
                        for (int y = y1; y <= y2; y++)
                            if (map[x][y]) {
                                flag = true;
                                v[x][y] = true;
                                dfs1(x, y, x1, y1, x2, y2);
                                break;
                            }
                        if (flag)
                            break;
                    }
                    if (!flag)
                        continue;
                    for (int x = x1; x <= x2; x++) {
                        for (int y = y1; y <= y2; y++)
                            if ((!map[x][y] && !vis[x][y] && !dfs2(x, y, x1, y1, x2, y2)) ||
                                (map[x][y] && !v[x][y])) {
                                flag = false;
                                break;
                            }
                        if (!flag)
                            break;
                    }
                    ans += flag;
                }
    printf("%lld\n", ans);
    return 0;
}

const int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };

void dfs1(const int& x, const int& y, const int& x1, const int& y1, const int& x2, const int& y2) {
    int tx, ty;
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        if (!(tx < x1 || x2 < tx || ty < y1 || y2 < ty) && map[tx][ty] && !v[tx][ty]) {
            v[tx][ty] = true;
            dfs1(tx, ty, x1, y1, x2, y2);
        }
    }
}

bool dfs2(const int& x, const int& y, const int& x1, const int& y1, const int& x2, const int& y2) {
    int tx, ty;
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        if (tx < x1 || x2 < tx || ty < y1 || y2 < ty)
            return true;
        if (!map[tx][ty] && !vis[tx][ty]) {
            vis[tx][ty] = true;
            if (dfs2(tx, ty, x1, y1, x2, y2))
                return true;
        }
    }
    return false;
}
