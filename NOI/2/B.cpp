#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010, sigma = 10;
int S[maxn][sigma], c;
int tmp[20], cnt;
bool f[maxn];
char v[20];

int main() {
    int t, n;
    scanf("%d", &t);
    int u;
    bool flag, ans;
    while (t--) {
        scanf("%d", &n);
        memset(f, false, sizeof(f));
        memset(S, 0, sizeof(S));
        c = 0;
        ans = true;
        while (n--) {
            memset(v, 0, sizeof(v));
            scanf("%s", v);
            cnt = 0;
            for (int i = strlen(v) - 1; i >= 0; i--) tmp[++cnt] = v[i] - '0';
            flag = false, u = 0;
            for (int i = cnt; i > 0; i--) {
                if (!S[u][tmp[i]])
                    S[u][tmp[i]] = ++c, flag = true;
                u = S[u][tmp[i]];
                if (f[u]) {
                    flag = false;
                    break;
                }
            }
            f[u] = true;
            if (!flag)
                ans = false;
        }
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
