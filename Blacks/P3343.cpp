
// Problem : P3343 [ZJOI2015]地震后的幻想乡
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P3343
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>
using namespace std;

const int maxn = 10, maxm = 50;
int G[maxn], cnt[1 << maxn];
double ans[1 << maxn][maxm];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        G[--x] |= (1 << (--y));
        G[y] |= (1 << x);
    }
    int max = 1 << n, t;
    for (int i = 1; i < max; i++) cnt[i] = cnt[i >> 1] + (i & 1);
    for (int s1 = 3; s1 < max; s1 += 2)
        for (int s2 = (s1 - 1) & s1; s2; s2 = (s2 - 1) & s1)
            if (s2 & 1) {
                t = 0;
                for (int i = 0; i < n; ++i)
                    if ((s1 >> i) & (~s2 >> i) & 1)
                        t += cnt[G[i] & s2];
                for (int i = 0; i <= m - t; ++i) ans[s1][i] += 1.0 / (i + t + 1) - ans[s2][i + t];
            }
    printf("%.6lf\n", ans[max - 1][0]);
    return 0;
}
