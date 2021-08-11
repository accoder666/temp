#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 110;
pair<long long, pair<int, int>> pPair[maxn * maxn];
bool flag[maxn][maxn];
int ans[maxn][maxn];
int b[maxn][maxn];
int p[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m;
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                scanf("%d", b[i] + j);
                pPair[(i - 1) * m + j].first = b[i][j];
                pPair[(i - 1) * m + j].second = make_pair(i, j);
            }
        sort(pPair + 1, pPair + n * m + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) flag[i][j] = false;
        for (int i = 1; i <= n; i++) p[i] = 1;
        for (int i = 1; i <= m; i++) flag[pPair[i].second.first][pPair[i].second.second] = true;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (pPair[i].second.first == j)
                    ans[j][i] = b[j][pPair[i].second.second];
                else {
                    while (flag[j][p[j]]) p[j]++;
                    ans[j][i] = b[j][p[j]], flag[j][p[j]++] = true;
                }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) printf("%d ", ans[i][j]);
            printf("\n");
        }
    }
    return 0;
}
