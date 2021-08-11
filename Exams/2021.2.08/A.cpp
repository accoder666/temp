#include <cstdio>
#include <cstring>
using namespace std;

const int maxp = 65;
int dfs(const int&, const int&, const int&, const int&);
int a[maxp], ans[maxp][maxp][maxp][maxp];
bool vis[maxp][maxp][maxp][maxp];
int n;

int main() {
    //    freopen("notepad.in", "r", stdin);
    //    freopen("notepad.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int q;
    scanf("%d", &q);
    int r1, c1, r2, c2;
    while (q--) {
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        memset(ans, 0x3f, sizeof(ans));
        memset(vis, false, sizeof(vis));
        printf("%d\n", dfs(r1, c1, r2, c2));
    }
    return 0;
}

inline int min(const int& x, const int& y) { return x < y ? x : y; }

inline int max(const int& x, const int& y) { return x > y ? x : y; }

int dfs(const int& i, const int& j, const int& k, const int& l) {
    if (i == k && j == l)
        return ans[i][j][k][l] = 0;
    if (vis[i][j][k][l])
        return ans[i][j][k][l];
    vis[i][j][k][l] = true;
    int ret = ans[0][0][0][0];
    ret = min(ret, dfs(max(i - 1, 1), min(a[max(i - 1, 1)], j), k, l));
    ret = min(ret, dfs(min(i + 1, n), min(a[min(i + 1, n)], j), k, l));
    ret = min(ret, dfs(i, max(0, j - 1), k, l));
    ret = min(ret, dfs(i, min(a[i], j + 1), k, l));
    ret = min(ret, dfs(i, 0, k, l));
    ret = min(ret, dfs(i, a[i], k, l));
    ret = min(ret, dfs(i, j, max(k - 1, 1), min(a[max(k - 1, 1)], l)));
    ret = min(ret, dfs(i, j, min(k + 1, n), min(a[min(i + 1, n)], j)));
    ret = min(ret, dfs(i, max(0, j - 1), k, l));
    ret = min(ret, dfs(i, min(a[i], j + 1), k, l));
    ret = min(ret, dfs(i, 0, k, l));
    ret = min(ret, dfs(i, a[i], k, l));
    return ans[i][j][k][l] = ++ret;
}
