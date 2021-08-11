#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000010;
int sa[maxn], rk[maxn], r[maxn << 1], id[maxn], cnt[maxn], a[maxn];
char s[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        s[i] = getchar();
        while (!isupper(s[i])) s[i] = getchar();
    }
    for (int i = n + 2; i <= (n << 1) + 1; i++) s[i] = s[(n << 1) + 2 - i];
    n = (n << 1) + 1;
    int lim = CHAR_MAX;
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
    for (int i = 1; i <= lim; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[rk[i]]--] = i;
    int p;
    for (int w = 1; w < n; w <<= 1) {
        p = 0;
        for (int i = n; i > n - w; i--) id[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w)
                id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[a[i] = rk[id[i]]]++;
        for (int i = 1; i <= lim; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) sa[cnt[a[i]]--] = id[i];
        memcpy(r, rk, sizeof(rk));
        p = 0;
        for (int i = 1; i <= n; i++)
            rk[sa[i]] = (p += (r[sa[i]] != r[sa[i - 1]] || r[sa[i] + w] != r[sa[i - 1] + w]));
        lim = p;
        if (lim >= n)
            break;
    }
    int L = 1, R = n >> 1, c = 0;
    while (L <= R) {
        printf("%c", rk[L] < rk[n - R + 1] ? s[L++] : s[R--]);
        if (++c == 80)
            printf("\n"), c = 0;
    }
    printf("\n");
    return 0;
}
