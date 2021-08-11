#include <chrono>
#include <cstdio>
#include <cstring>
#include <random>
using namespace std;

const int maxn = 200010, maxm = 70, maxp = 15;
long long s[maxn];
int a[maxp + 10];
int Cnt[(1 << maxp) + 10], sum[(1 << maxp) + 10];
char Ans[maxm];

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    int lim = (int)ceill((long double)n / 2);
    char ch;
    for (int i = 1; i <= n; i++) {
        ch = getchar();
        while (ch != '0' && ch != '1') ch = getchar();
        for (int j = 0; j < m; j++) s[i] |= ((long long)(ch == '1') << j), ch = getchar();
    }
    long long ans = 0, tmp;
    int val = 0, P, pop;
    mt19937 r(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> R(1, n);
    for (int it = 1; it <= 10; it++) {
        P = R(r), pop = 0;
        for (int j = 0; j < m; j++)
            if (s[P] & (1ll << j))
                a[pop++] = j;
        memset(Cnt, 0, sizeof(Cnt));
        for (int j = 1; j <= n; j++) {
            tmp = 0;
            for (int k = 0; k < pop; k++)
                if (s[j] & (1ll << a[k]))
                    tmp |= (1ll << k);
            Cnt[tmp]++;
        }
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < (1 << pop); i++)
            for (int j = i; j; j = (j - 1) & i) sum[j] += Cnt[i];
        for (int i = 0; i < (1 << pop); i++)
            if (sum[i] >= lim && val < __builtin_popcount(i)) {
                val = __builtin_popcount(i), ans = 0;
                for (int j = 0; j < pop; j++)
                    if (i & (1 << j))
                        ans |= (1ll << a[j]);
            }
    }
    for (int i = 0; i < m; i++) Ans[i] = ((ans >> i) & 1) + '0';
    printf("%s\n", Ans);
    return 0;
}
