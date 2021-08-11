
// Problem : P3175 [HAOI2015]按位或
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P3175
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>
using namespace std;

const int maxn = 20;
double p[1 << maxn];
int cnt[1 << maxn];

int main() {
    int n;
    scanf("%d", &n);
    int max = 1 << n;
    for (int i = 0; i < max; i++) scanf("%lf", p + i), cnt[i] = cnt[i >> 1] + (i & 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < max; j++)
            if ((j >> i) & 1)
                p[j] += p[j ^ (1 << i)];
    double ans = 0;
    for (int i = 1; i < max; i++) {
        if (1 - p[(max - 1) ^ i] < 1e-6) {
            printf("INF\n");
            return 0;
        }
        ans += ((cnt[i] & 1) ? 1 : -1) / (1 - p[(max - 1) ^ i]);
    }
    printf("%.10lf\n", ans);
    return 0;
}
