#include <cstdio>
using namespace std;

const int maxn = 10;
bool dfs(const int&, const int&, const int&);
int map[maxn][maxn];

int main() {
    int t;
    scanf("%d", &t);
    getchar();
    char ch;
    int x, y;
    bool flag;
    while (t--) {
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 5; j++) {
                ch = getchar();
                map[i][j] = (ch == '*') ? 2 : (ch - '0');
                if (ch == '*')
                    x = i, y = j;
            }
            getchar();
        }
        flag = false;
        for (int dep = 0; dep <= 15; dep++)
            if (dfs(x, y, dep)) {
                printf("%d\n", dep);
                flag = true;
                break;
            }
        if (!flag)
            printf("-1\n");
    }
    return 0;
}

const int goal[maxn][maxn] = { { 0, 0, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1, 1 }, { 0, 0, 1, 1, 1, 1 },
                               { 0, 0, 0, 2, 1, 1 }, { 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 0 } };
inline int cal(void) {
    int ret = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++) ret += (map[i][j] != goal[i][j]);
    return ret;
}

int vis[maxn][maxn];
const int dx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 }, dy[8] = { 1, -1, 2, -2, 2, -2, 1, -1 };
bool dfs(const int& x, const int& y, const int& dep) {
    if (!dep)
        return !cal();
    int tx, ty;
    vis[x][y] = dep;
    for (int i = 0; i < 8; i++) {
        tx = x + dx[i], ty = y + dy[i];
        if (tx >= 1 && tx <= 5 && ty >= 1 && ty <= 5 && vis[tx][ty] != dep + 1) {
            map[x][y] ^= map[tx][ty] ^= map[x][y] ^= map[tx][ty];
            if (cal() <= dep && dfs(tx, ty, dep - 1))
                return true;
            map[x][y] ^= map[tx][ty] ^= map[x][y] ^= map[tx][ty];
        }
    }
    vis[x][y] = 0;
    return false;
}
