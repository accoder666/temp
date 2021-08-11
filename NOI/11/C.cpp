#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1000010, maxs = 1010;
int L[maxs], R[maxs], id[maxn];
inline void reset(const int&);
vector<int> v[maxs];
int tag[maxs];
int a[maxn];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int len = (int)sqrtl((long double)n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++) L[i] = R[i - 1] + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++)
        for (int j = L[i]; j <= R[i]; j++) id[j] = i;
    for (int i = 1; i <= num; i++) reset(i);
    char opt;
    int l, r, c;
    int ans;
    while (q--) {
        opt = getchar();
        while (opt != 'A' && opt != 'M') opt = getchar();
        scanf("%d %d %d", &l, &r, &c);
        switch (opt) {
            case 'A':
                ans = 0;
                if (id[l] == id[r]) {
                    for (int i = l; i <= r; i++)
                        if (a[i] + tag[id[i]] >= c)
                            ans++;
                } else {
                    for (int i = l; i <= R[id[l]]; i++)
                        if (a[i] + tag[id[i]] >= c)
                            ans++;
                    for (int i = L[id[r]]; i <= r; i++)
                        if (a[i] + tag[id[i]] >= c)
                            ans++;
                    for (int i = id[l] + 1; i < id[r]; i++)
                        ans += v[i].end() - lower_bound(v[i].begin(), v[i].end(), c - tag[i]);
                }
                printf("%d\n", ans);
                break;
            case 'M':
                if (id[l] == id[r]) {
                    for (int i = l; i <= r; i++) a[i] += c;
                    reset(id[l]);
                } else {
                    for (int i = l; i <= R[id[l]]; i++) a[i] += c;
                    for (int i = L[id[r]]; i <= r; i++) a[i] += c;
                    reset(id[l]), reset(id[r]);
                    for (int i = id[l] + 1; i < id[r]; i++) tag[i] += c;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

inline void reset(const int& p) {
    v[p].clear();
    for (int i = L[p]; i <= R[p]; i++) v[p].push_back(a[i]);
    sort(v[p].begin(), v[p].end());
    return;
}
