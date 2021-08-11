#include <algorithm>
#include <cstdio>
using namespace std;

unsigned long long base = 19260817, mod1 = 1000000007, mod2 = 1000000009;
const int maxn = 50010, maxp = 210, maxm = 20;
unsigned long long h[maxp * maxp];
unsigned long long p[2][maxn];
char s[maxn];
int r[maxm];

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    p[0][0] = p[1][0] = 1;
    for (int i = 1; i < n; i++) {
        p[0][i] = p[0][i - 1] * base % mod1;
        p[1][i] = p[1][i - 1] * base % mod2;
    }
    int cnt = 0, c;
    unsigned long long t1, t2;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            c = 0;
            for (int k = 0; k < m; k++) r[k] = 0;
            for (int k = i; k <= j; k++)
                if (!r[s[k] - 'a'])
                    r[s[k] - 'a'] = ++c;
            t1 = t2 = 0;
            for (int k = i; k <= j; k++)
                t1 = (t1 + p[0][k - i] * r[s[k] - 'a']) % mod1,
                t2 = (t2 + p[1][k - i] * r[s[k] - 'a']) % mod2;
            h[++cnt] = t1 + mod1 * t2;
        }
    sort(h + 1, h + cnt + 1);
    printf("%d\n", unique(h + 1, h + cnt + 1) - (h + 1));
    return 0;
}
