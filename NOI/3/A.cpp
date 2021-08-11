#include <cstdio>
using namespace std;

const int maxn = 210, maxk = 8;
int C[(1 << maxk) + 10][(1 << maxk) + 10][maxn];
int ans[maxn];

int main() {
    int k, w;
    scanf("%d %d", &k, &w);
    int max = 1 << k;
    C[1][1][0] = 1;
    for (int i = 0; i < max; i++) C[i][0][0] = C[i][0][1] = C[i][i][0] = C[i][i][1] = 1;
    for (int i = 1; i < max; i++)
        for (int j = 1, l; j < i; j++) {
            for (l = 1; l <= C[i - 1][j][0] || l <= C[i - 1][j - 1][0] || C[i][j][l]; l++)
                C[i][j][l] += C[i - 1][j][l] + C[i - 1][j - 1][l], C[i][j][l + 1] += C[i][j][l] / 10,
                    C[i][j][l] %= 10;
            C[i][j][0] = l - 1;
        }
    for (int i = 2, l; i <= w / k; i++) {
        if (i > max - 1)
            break;
        for (l = 1; l <= ans[0] || l <= C[max - 1][i][0] || ans[l]; l++)
            ans[l] += C[max - 1][i][l], ans[l + 1] += ans[l] / 10, ans[l] %= 10;
        ans[0] = l - 1;
    }
    for (int i = 1, l; i <= (1 << (w % k)) - 1; i++) {
        if (w / k > max - 1 - i)
            break;
        for (l = 1; l <= ans[0] || l <= C[max - 1 - i][w / k][0] || ans[l]; l++)
            ans[l] += C[max - 1 - i][w / k][l], ans[l + 1] += ans[l] / 10, ans[l] %= 10;
        ans[0] = l - 1;
    }
    for (int i = ans[0]; i; i--) printf("%d", ans[i]);
    printf("\n");
    return 0;
}
