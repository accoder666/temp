#include <cstdio>
using namespace std;

const int maxn = 510;
int x[maxn], y[maxn];
int p[maxn][maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", p[i] + i), x[p[i][i]] = y[p[i][i]] = i;
    int t;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) t = (x[i] < x[j]), p[x[j] += !t][y[j] -= t] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) printf("%d ", p[i][j]);
        printf("\n");
    }
    return 0;
}
