#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 20;
long double A[maxn][maxn];
long double p[maxn][maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++) scanf("%Lf", p[i] + j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            A[i][j] = 2 * (p[i][j] - p[i + 1][j]);
            A[i][n + 1] += p[i][j] * p[i][j] - p[i + 1][j] * p[i + 1][j];
        }
    for (int i = 1, r; i <= n; i++) {
        r = i;
        for (int j = i + 1; j <= n; j++)
            if (fabsl(A[j][i]) > fabsl(A[r][i]))
                r = j;
        if (i != r)
            for (int j = 1; j <= n + 1; j++) swap(A[r][j], A[i][j]);
        for (int j = n + 1; j > i; j--)
            for (int k = i + 1; k <= n; k++) A[k][j] -= A[k][i] / A[i][i] * A[i][j];
    }
    for (int i = n; i > 0; i--) {
        for (int j = i + 1; j <= n; j++) A[i][n + 1] -= A[j][n + 1] * A[i][j];
        A[i][n + 1] /= A[i][i];
    }
    for (int i = 1; i <= n; i++) printf("%.3Lf ", A[i][n + 1]);
    printf("\n");
    return 0;
}
