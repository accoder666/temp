#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxs = 350;
inline void init(void);
inline void modify(int, int, int, int);
inline int query(int, int, int);
int a[maxn];
int n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    init();
    int opt, l, r, x, y, k;
    while (m--) {
        scanf("%d %d %d", &opt, &l, &r);
        switch (opt) {
            case 1:
                scanf("%d %d", &x, &y);
                modify(l, r, x, y);
                break;
            case 2:
                scanf("%d", &k);
                printf("%d\n", query(l, r, k));
                break;
            default:
                break;
        }
    }
    return 0;
}

int rt[maxs][maxn], val[maxn], fa[maxn];

int find(const int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

inline void merge(const int p, const int x, const int y) {
    if (!rt[p][x])
        return;
    if (!rt[p][y])
        val[rt[p][y] = rt[p][x]] = y;
    else
        fa[rt[p][x]] = rt[p][y];
    rt[p][x] = 0;
    return;
}

const int maxv = 100000;
int L[maxs], R[maxs], id[maxn];
int Min[maxs], Max[maxs], bel[maxn];
int cnt[maxs][maxn], sum[maxs][maxs];

inline void init(void) {
    int len = (int)sqrtl(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++) L[i] = R[i - 1] + 1, R[i] = i * len;
    R[num] = n;
    for (int i = 1; i <= num; i++)
        for (int j = L[i]; j <= R[i]; j++) id[j] = i;
    len = (int)sqrtl(maxv), num = (maxv - 1) / len + 1;
    for (int i = 1; i <= num; i++) Min[i] = Max[i - 1] + 1, Max[i] = i * len;
    Max[num] = maxv;
    for (int i = 1; i <= num; i++)
        for (int j = Min[i]; j <= Max[i]; j++) bel[j] = i;
    for (int i = 1; i <= id[n]; i++) {
        for (int j = 1; j <= maxv; j++) cnt[i][j] = cnt[i - 1][j];
        for (int j = 1; j <= bel[maxv]; j++) sum[i][j] = sum[i - 1][j];
        for (int j = L[i]; j <= R[i]; j++) cnt[i][a[j]]++, sum[i][bel[a[j]]]++;
    }
    for (int i = 1; i <= id[n]; i++)
        for (int j = L[i]; j <= R[i]; j++) {
            if (!rt[i][a[j]])
                val[rt[i][a[j]] = j] = a[j];
            fa[j] = rt[i][a[j]];
        }
    return;
}

inline void build(const int p, const int l, const int r, const int x, const int y) {
    for (int i = L[p]; i <= R[p]; i++) a[i] = val[find(i)], rt[p][a[i]] = 0;
    for (int i = l; i <= r; i++)
        if (a[i] == x)
            a[i] = y;
    for (int i = L[p]; i <= R[p]; i++) {
        if (!rt[p][a[i]])
            val[rt[p][a[i]] = i] = a[i];
        fa[i] = rt[p][a[i]];
    }
    return;
}

inline void modify(const int l, const int r, const int x, const int y) {
    if (x == y)
        return;
    int c = 0;
    if (id[l] == id[r]) {
        for (int i = l; i <= r; i++) c += (val[find(i)] == x);
        if (!c)
            return;
        for (int i = id[r]; i <= id[n]; i++)
            cnt[i][x] -= c, cnt[i][y] += c, sum[i][bel[x]] -= c, sum[i][bel[y]] += c;
        build(id[l], l, r, x, y);
    } else {
        bool f1 = false, f2 = false;
        for (int i = l; i <= R[id[l]]; i++) c += (val[find(i)] == x), f1 |= (val[find(i)] == x);
        int tmp = 0;
        for (int i = id[l]; i < id[r]; i++) {
            c += tmp;
            sum[i][bel[x]] -= c, sum[i][bel[y]] += c;
            tmp = cnt[i + 1][x] - cnt[i][x];
            cnt[i][x] -= c, cnt[i][y] += c;
        }
        for (int i = L[id[r]]; i <= r; i++) c += (val[find(i)] == x), f2 |= (val[find(i)] == x);
        for (int i = id[r]; i <= id[n]; i++)
            cnt[i][x] -= c, cnt[i][y] += c, sum[i][bel[x]] -= c, sum[i][bel[y]] += c;
        for (int i = id[l] + 1; i < id[r]; i++) merge(i, x, y);
        if (f1)
            build(id[l], l, R[id[l]], x, y);
        if (f2)
            build(id[r], L[id[r]], r, x, y);
    }
    return;
}

inline int query(const int l, const int r, int k) {
    static int Cnt[maxn], Sum[maxs];
    if (id[l] == id[r])
        for (int i = l; i <= r; i++) Cnt[val[find(i)]]++, Sum[bel[val[find(i)]]]++;
    else {
        for (int i = l; i <= R[id[l]]; i++) Cnt[val[find(i)]]++, Sum[bel[val[find(i)]]]++;
        for (int i = L[id[r]]; i <= r; i++) Cnt[val[find(i)]]++, Sum[bel[val[find(i)]]]++;
    }
    int ret = -1, tmp;
    for (int i = 1; i <= bel[maxv]; i++) {
        tmp = sum[id[r] - (id[l] != id[r])][i] - sum[id[l]][i] + Sum[i];
        if (k <= tmp) {
            for (int j = Min[i]; j <= Max[i]; j++) {
                k -= cnt[id[r] - (id[l] != id[r])][j] - cnt[id[l]][j] + Cnt[j];
                if (k <= 0) {
                    ret = j;
                    break;
                }
            }
            break;
        }
        k -= tmp;
    }
    if (id[l] == id[r])
        for (int i = l; i <= r; i++) Cnt[val[find(i)]]--, Sum[bel[val[find(i)]]]--;
    else {
        for (int i = l; i <= R[id[l]]; i++) Cnt[val[find(i)]]--, Sum[bel[val[find(i)]]]--;
        for (int i = L[id[r]]; i <= r; i++) Cnt[val[find(i)]]--, Sum[bel[val[find(i)]]]--;
    }
    return ret;
}
