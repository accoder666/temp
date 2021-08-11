#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 40010, maxs = 210;
int a[maxn], b[maxn];
vector<int> p[maxn];
int rk[maxn];
int L[maxs], R[maxs], id[maxn];
int bucket[maxn];
pair<int, int> P[maxs][maxs];
inline void update(pair<int, int>&, const pair<int, int>&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
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
            P[i][j] = P[i][j - 1];
            for (int k = L[j]; k <= R[j]; k++) update(P[i][j], make_pair(++bucket[a[k]], a[k]));
        }
    }
    int l, r, x = 0;
    pair<int, int> ans;
    while (m--) {
        scanf("%d %d", &l, &r);
        l = (l + x - 1) % n + 1, r = (r + x - 1) % n + 1;
        if (l > r)
            l ^= r ^= l ^= r;
        if (id[l] == id[r]) {
            ans = make_pair(0, 0);
            for (int i = l; i <= r; i++) bucket[a[i]] = 0;
            for (int i = l; i <= r; i++) update(ans, make_pair(++bucket[a[i]], a[i]));
        } else {
            ans = P[id[l] + 1][id[r] - 1];
            for (int i = l; i <= R[id[l]]; i++) {
                if (a[i] < ans.second && rk[i] + ans.first - 1 < p[a[i]].size() &&
                    p[a[i]][rk[i] + ans.first - 1] <= r)
                    ans.second = a[i];
                while (rk[i] + ans.first < p[a[i]].size() && p[a[i]][rk[i] + ans.first] <= r)
                    ans.first++, ans.second = a[i];
            }
            for (int i = L[id[r]]; i <= r; i++) {
                if (a[i] < ans.second && rk[i] - ans.first + 1 >= 0 && p[a[i]][rk[i] - ans.first + 1] >= l)
                    ans.second = a[i];
                while (rk[i] - ans.first >= 0 && p[a[i]][rk[i] - ans.first] >= l)
                    ans.first++, ans.second = a[i];
            }
        }
        printf("%d\n", x = b[ans.second]);
    }
    return 0;
}

inline void update(pair<int, int>& x, const pair<int, int>& y) {
    if (x.first < y.first || (x.first == y.first && x.second > y.second))
        x = y;
    return;
}
