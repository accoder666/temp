#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

const int maxn = 200010;
int l[maxn], r[maxn], v[maxn];
char S[maxn];

int main() {
    int len = 0;
    S[len] = '#';
    char ch;
    while (islower(ch = getchar())) S[++len] = ch, S[++len] = '#';
    int m = 0, p = 0;
    for (int i = 0; i <= len; i++) {
        v[i] = (i < p ? min(v[(m << 1) - i], p - i) : 1);
        while (i - v[i] >= 0 && i + v[i] <= len && S[i - v[i]] == S[i + v[i]]) v[i]++;
        if (i + v[i] > p)
            m = i, p = i + v[i];
        l[i + v[i] - 1] = max(l[i + v[i] - 1], v[i] - 1);
        r[i - v[i] + 1] = max(r[i - v[i] + 1], v[i] - 1);
    }
    for (int i = 2; i <= len; i += 2) r[i] = max(r[i], r[i - 2] - 2);
    for (int i = len - 2; i >= 0; i -= 2) l[i] = max(l[i], l[i + 2] - 2);
    int ans = 0;
    for (int i = 0; i <= len; i += 2)
        if (l[i] && r[i])
            ans = max(ans, l[i] + r[i]);
    printf("%d\n", ans);
    return 0;
}
