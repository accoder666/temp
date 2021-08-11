#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const int maxn = 1100, maxlg = 40;
long long s[maxlg][maxn << 2], val[maxn << 2];
long long tmp[maxn << 2];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    static const int maxl = 810;
    s[0][1] = 1;
    for (int i = 1; i < maxlg; i++) {
        for (int j = k; j <= k + maxl; j++) tmp[j - k] = s[i - 1][j];
        for (int j = 1; j <= maxl << 1; j++)
            for (int l = 0; l <= j; l++) s[i][j] = (s[i][j] + s[i - 1][l] * tmp[j - l]) % mod;
        for (int j = 1; j <= maxl; j++) s[i][j] = s[i][j + maxl];
    }
    for (int i = maxlg - 1; i >= 0; i--)
        if (n & (1LL << i)) {
            for (int j = 1; j <= maxl; j++) tmp[j] = j;
        }
}
