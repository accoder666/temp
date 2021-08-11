#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010;
int a[maxn], b[maxn], c[maxn];
int nxt[maxn], head[maxn];
int f[maxn];
int x[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m;
    bool flag;
    int last;
    while (t--) {
        scanf("%d %d", &n, &m);
        memset(a, 0, sizeof(int) * (n + 5));
        memset(b, 0, sizeof(int) * (n + 5));
        memset(c, 0, sizeof(int) * (m + 5));
        memset(nxt, 0, sizeof(int) * (n + 5));
        memset(head, 0, sizeof(int) * (n + 5));
        memset(f, 0, sizeof(int) * (n + 5));
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) {
            scanf("%d", b + i);
            f[b[i]] = i;
            if (a[i] != b[i])
                nxt[i] = head[b[i]], head[b[i]] = i;
        }
        flag = true, last = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", c + i);
            if (!f[c[i]]) {
                flag = false;
                if (!last)
                    last = i;
            } else {
                flag = true;
                if (head[c[i]]) {
                    a[head[c[i]]] = c[i];
                    x[i] = head[c[i]];
                    head[c[i]] = nxt[head[c[i]]];
                } else
                    x[i] = f[c[i]];
                if (last) {
                    for (int j = last; j < i; j++)
                        if (!f[c[j]])
                            x[j] = x[i];
                    last = 0;
                }
            }
        }
        for (int i = 1; i <= n; i++) flag &= (a[i] == b[i]);
        printf(flag ? "YES\n" : "NO\n");
        if (flag) {
            for (int i = 1; i <= m; i++) printf("%d ", x[i]);
            printf("\n");
        }
    }
    return 0;
}
