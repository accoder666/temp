#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 60;
const long double eps = 1e-7;
long double A[maxn][maxn];

int main() {
    int n;
    scanf("%d", &n);
    long double g, c = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%Lf", &g);
            if (i < j) {
                if (g > 1 - eps)
                    g = 1 - eps;
                c *= (1 - g), g /= (1 - g);
                A[i][i] += g, A[j][j] += g, A[i][j] -= g, A[j][i] -= g;
            }
        }
    int r;
    long double ans = 1, tmp;
    for (int i = 1; i < n; i++) {
        r = i;
        for (int j = i + 1; j < n; j++)
            if (fabsl(A[j][i]) > fabs(A[r][i]))
                r = j;
        if (r != i) {
            for (int j = i + 1; j < n; j++) tmp = A[i][j], A[i][j] = A[r][j], A[r][j] = tmp;
            ans = -ans;
        }
        for (int j = i + 1; j < n; j++) {
            tmp = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) A[j][k] -= tmp * A[i][k];
        }
        ans *= A[i][i];
    }
    printf("%.20Lf\n", ans * c);
    return 0;
}
