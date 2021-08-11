#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010, maxs = 320;
int L[maxs], R[maxs], id[maxn];
int cnt[maxs][maxn], val[maxs][maxs];
int b[maxn];
int a[maxn];

int main() {
    int n, c, m;
    scanf("%d %d %d", &n, &c, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int len = (int)sqrtl((long double)n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++) L[i] = R[i - 1] + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= c; j++) cnt[i][j] = cnt[i - 1][j];
        for (int j = L[i]; j <= R[i]; j++) id[j] = i, cnt[i][a[j]]++;
    }
    for (int i = 1; i <= num; i++) {
        for (int j = i; j <= num; j++) {
            val[i][j] = val[i][j - 1];
            for (int k = L[j]; k <= R[j]; k++) {
                if (b[a[k]] & 1)
                    val[i][j]++;
                else if (b[a[k]])
                    val[i][j]--;
                b[a[k]]++;
            }
        }
        memset(b, 0, sizeof(int) * (c + 5));
    }
    int l, r, ans = 0;
    int tmp;
    while (m--) {
        scanf("%d %d", &l, &r);
        l = (l + ans) % n + 1, r = (r + ans) % n + 1;
        if (l > r)
            l ^= r ^= l ^= r;
        if (id[l] == id[r]) {
            ans = 0;
            for (int i = l; i <= r; i++) {
                if (b[a[i]] & 1)
                    ans++;
                else if (b[a[i]])
                    ans--;
                b[a[i]]++;
            }
            for (int i = l; i <= r; i++) b[a[i]] = 0;
        } else {
            ans = val[id[l] + 1][id[r] - 1];
            for (int i = l; i <= R[id[l]]; i++) {
                tmp = b[a[i]] + cnt[id[r] - 1][a[i]] - cnt[id[l]][a[i]];
                if (tmp & 1)
                    ans++;
                else if (tmp)
                    ans--;
                b[a[i]]++;
            }
            for (int i = L[id[r]]; i <= r; i++) {
                tmp = b[a[i]] + cnt[id[r] - 1][a[i]] - cnt[id[l]][a[i]];
                if (tmp & 1)
                    ans++;
                else if (tmp)
                    ans--;
                b[a[i]]++;
            }
            for (int i = l; i <= R[id[l]]; i++) b[a[i]] = 0;
            for (int i = L[id[r]]; i <= r; i++) b[a[i]] = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}
