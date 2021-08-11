#include <cstdio>
using namespace std;

const int maxn = 300010;
int L[maxn], R[maxn], U[maxn], D[maxn];
int f[maxn], s[maxn];
int r[maxn], c[maxn];
int cnt;
bool dfs(const int&);
int ans[maxn], len;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= m; i++) L[i] = i - 1, R[i] = i + 1, U[i] = D[i] = i;
    L[0] = m, R[m] = 0, cnt = m;
    int val;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &val);
            if (val) {
                cnt++;
                r[cnt] = i, c[cnt] = j, s[j]++;
                D[cnt] = D[j], U[D[j]] = cnt, U[cnt] = j, D[j] = cnt;
                if (!f[i])
                    f[i] = L[cnt] = R[cnt] = cnt;
                else {
                    R[cnt] = R[f[i]], L[R[f[i]]] = cnt;
                    L[cnt] = f[i], R[f[i]] = cnt;
                }
            }
        }
    if (!dfs(1))
        printf("-1\n");
    else {
        for (int i = 1; i <= len; i++) printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}

inline void remove(const int& p) {
    L[R[p]] = L[p], R[L[p]] = R[p];
    for (int i = D[p]; i != p; i = D[i])
        for (int j = R[i]; j != i; j = R[j]) U[D[j]] = U[j], D[U[j]] = D[j], s[c[j]]--;
    return;
}

inline void restore(const int& p) {
    for (int i = U[p]; i != p; i = U[i])
        for (int j = L[i]; j != i; j = L[j]) U[D[j]] = D[U[j]] = j, s[c[j]]++;
    L[R[p]] = R[L[p]] = p;
    return;
}

bool dfs(const int& dep) {
    if (!R[0]) {
        len = dep - 1;
        return true;
    }
    int p = R[0];
    for (int i = p; i; i = R[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = D[p]; i != p; i = D[i]) {
        ans[dep] = r[i];
        for (int j = R[i]; j != i; j = R[j]) remove(c[j]);
        if (dfs(dep + 1))
            return true;
        for (int j = L[i]; j != i; j = L[j]) restore(c[j]);
    }
    restore(p);
    return false;
}
