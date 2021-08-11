#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 100010, maxlg = 18;
int p[maxn], cnt;
int pr[maxn];
vector<int> vec[maxn];
bool f[maxn];
int b[maxn], l[maxn];
int nxt[maxn][maxlg];
int a[maxn];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int v = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (v < a[i])
            v = a[i];
    }
    v += 5;
    for (int i = 2; i <= v; i++) {
        if (!f[i])
            p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= v; j++) {
            f[i * p[j]] = true, pr[i * p[j]] = p[j];
            if (!(i % p[j]))
                break;
        }
    }
    int tmp, tmpp;
    for (int i = 1; i <= n; i++) {
        tmp = a[i];
        while (f[tmp]) {
            vec[i].push_back(tmpp = pr[tmp]);
            while (!(tmp % tmpp)) tmp /= tmpp;
        }
        vec[i].push_back(tmp);
    }
    l[0] = 1;
    for (int i = 1; i <= n; i++) {
        tmp = a[i], l[i] = l[i - 1];
        while (f[tmp]) {
            tmpp = pr[tmp];
            b[tmpp]++;
            while (b[tmpp] > 1) {
                for (int j : vec[l[i]]) b[j]--;
                l[i]++;
            }
            while (!(tmp % tmpp)) tmp /= tmpp;
        }
        if (tmp == 1)
            continue;
        b[tmp]++;
        while (b[tmp] > 1) {
            for (int j : vec[l[i]]) b[j]--;
            l[i]++;
        }
    }
    for (int i = 1; i <= n; i++) nxt[i][0] = l[i] - 1;
    for (int i = 1; i < maxlg; i++)
        for (int j = 1; j <= n; j++) nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
    int x, y;
    int ans;
    while (q--) {
        ans = 1;
        scanf("%d %d", &x, &y);
        for (int i = maxlg - 1; i >= 0; i--)
            if (nxt[y][i] >= x)
                ans += (1 << i), y = nxt[y][i];
        printf("%d\n", ans);
    }
    return 0;
}
