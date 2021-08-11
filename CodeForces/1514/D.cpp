#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 300010, maxs = 600;
int a[maxn], b[maxn];
vector<int> p[maxn];
int rk[maxn];
int L[maxs], R[maxs], id[maxn];
int bucket[maxn];
int cnt[maxs][maxs];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
    sort(b + 1, b + n + 1);
    int c = unique(b + 1, b + n + 1) - (b + 1);
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + c + 1, a[i]) - b;
    for (int i = 1; i <= n; i++) rk[i] = p[a[i]].size(), p[a[i]].push_back(i);
    int len = (int)sqrtl((long double)n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++) L[i] = R[i - 1] + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++) {
        memset(bucket, 0, sizeof(int) * (c + 5));
        for (int j = L[i]; j <= R[i]; j++) id[j] = i;
        for (int j = i; j <= num; j++) {
            cnt[i][j] = cnt[i][j - 1];
            for (int k = L[j]; k <= R[j]; k++)
                if (cnt[i][j] < (++bucket[a[k]]))
                    cnt[i][j] = bucket[a[k]];
        }
    }
    int l, r;
    int ans;
    while (q--) {
        scanf("%d %d", &l, &r);
        ans = 0;
        if (id[l] == id[r]) {
            for (int i = l; i <= r; i++) bucket[a[i]] = 0;
            for (int i = l; i <= r; i++)
                if (ans < (++bucket[a[i]]))
                    ans = bucket[a[i]];
        } else {
            ans = cnt[id[l] + 1][id[r] - 1];
            for (int i = l; i <= R[id[l]]; i++)
                while (rk[i] + ans < p[a[i]].size() && p[a[i]][rk[i] + ans] <= r) ans++;
            for (int i = L[id[r]]; i <= r; i++)
                while (rk[i] - ans >= 0 && p[a[i]][rk[i] - ans] >= l) ans++;
        }
        printf("%d\n", max((ans << 1) - (r - l + 1), 1));
    }
    return 0;
}
