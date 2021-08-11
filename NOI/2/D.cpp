#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 1000010;
char M[1 << CHAR_BIT], S[maxn];
int val[maxn], len = 1;

int main() {
    int n;
    scanf("%d", &n);
    S[0] = '#', S[1] = getchar();
    while (S[1] != '0' && S[1] != '1') S[1] = getchar();
    S[++len] = '#';
    while (--n) S[++len] = getchar(), S[++len] = '#';
    M['0'] = '1', M['1'] = '0', M['#'] = '#';
    int m = 0, r = 0;
    long long ans = 0;
    for (int i = 0; i <= len; i += 2) {
        val[i] = (i < r ? min(r - i, val[(m << 1) - i]) : 1);
        while (i >= val[i] && i + val[i] <= len && S[i - val[i]] == M[S[i + val[i]]]) val[i]++;
        if (i + val[i] > r)
            r = i + val[i], m = i;
        ans += val[i] >> 1;
    }
    printf("%lld\n", ans);
    return 0;
}
