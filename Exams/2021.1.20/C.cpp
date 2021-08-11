#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int ST[2][20][maxn], lg[maxn];
inline int query(const int&, const int&, const int&);

int main() {
    freopen("jie.in", "r", stdin);
    freopen("jie.out", "w", stdout);
    int n, k;
    scanf("%d %d", &n, &k);
    lg[1] = 0;
    for (int i = 1; i <= n; i++) scanf("%d", ST[0][0] + i), ST[1][0][i] = ST[0][0][i], lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < lg[n]; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            ST[0][i][j] = max(ST[0][i - 1][j], ST[0][i - 1][j + (1 << (i - 1))]),
            ST[1][i][j] = min(ST[1][i - 1][j], ST[1][i - 1][j + (1 << (i - 1))]);
    int ans = 0;
    for (int l1 = 1; l1 <= n; l1++)
        for (int r1 = l1 + 1; r1 <= n; r1++)
            if (query(0, l1, r1) - query(1, l1, r1) == r1 - l1)
                for (int l2 = 1; l2 <= n; l2++)
                    for (int r2 = l2 + 1; r2 <= n; r2++)
                        if (!(l1 <= l2 && r2 <= r1) && !(l2 <= l1 && r1 <= r2) &&
                            (r1 - l1 + r2 - l2 + 1 - (l1 < l2 ? (r1 - l2) : (r2 - l1))) >= k &&
                            query(0, l2, r2) - query(1, l2, r2) == r2 - l2)
                            ans++;
    printf("%d\n", ans);
    return 0;
}

inline int query(const int& t, const int& l, const int& r) {
    int v = lg[r - l + 1];
    if (t)
        return min(ST[t][v - 1][l], ST[t][v - 1][r - (1 << (v - 1)) + 1]);
    return max(ST[t][v - 1][l], ST[t][v - 1][r - (1 << (v - 1)) + 1]);
}
