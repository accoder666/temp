#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxs = 1010;
int L[maxs], R[maxs], bel[maxn];
long long a[maxn], tag[maxs];
inline void rebuild(int);
long long vec[maxs][maxs];

int main() {
    freopen("ds.in", "r", stdin);
    freopen("ds.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    int len = 100, num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++) L[i] = R[i - 1] + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++) {
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
        rebuild(i);
    }
    int m;
    scanf("%d", &m);
    int opt, l, r, ans;
    long long v;
    while (m--) {
        scanf("%d %d %d %lld", &opt, &l, &r, &v);
        switch (opt) {
            case 1:
                if (bel[l] == bel[r]) {
                    for (int i = l; i <= r; i++) a[i] += v;
                    rebuild(bel[l]);
                } else {
                    for (int i = l; i <= R[bel[l]]; i++) a[i] += v;
                    for (int i = L[bel[r]]; i <= r; i++) a[i] += v;
                    rebuild(bel[l]), rebuild(bel[r]);
                    for (int i = bel[l] + 1; i < bel[r]; i++) tag[i] += v;
                }
                break;
            case 2:
                ans = 0;
                if (bel[l] == bel[r])
                    for (int i = l; i <= r; i++) ans += (a[i] + tag[bel[l]] <= v);
                else {
                    for (int i = l; i <= R[bel[l]]; i++) ans += (a[i] + tag[bel[l]] <= v);
                    for (int i = L[bel[r]]; i <= r; i++) ans += (a[i] + tag[bel[r]] <= v);
                    for (int i = bel[l] + 1; i < bel[r]; i++)
                        ans += lower_bound(vec[i] + 1, vec[i] + (R[i] - L[i] + 1) + 1, v - tag[i] + 1) -
                               (vec[i] + 1);
                }
                printf("%d\n", ans);
                break;
            default:
                break;
        }
    }
    return 0;
}

inline void rebuild(const int p) {
    for (int i = L[p]; i <= R[p]; i++) vec[p][i - L[p] + 1] = a[i];
    sort(vec[p] + 1, vec[p] + (R[p] - L[p] + 1) + 1);
    return;
}
