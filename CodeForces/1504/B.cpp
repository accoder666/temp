#include <cstdio>
using namespace std;

const int maxn = 300010;
bool a[maxn], b[maxn];
int sum[maxn];
int p[maxn], c;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    char ch;
    bool ans, flag;
    while (t--) {
        scanf("%d", &n);
        c = 0;
        ch = getchar();
        while (ch != '0' && ch != '1') ch = getchar();
        for (int i = 1; i <= n; i++) {
            a[i] = ch - '0', ch = getchar();
            sum[i] = sum[i - 1] + (a[i] ? 1 : -1);
            if (!sum[i])
                p[++c] = i;
        }
        ch = getchar();
        while (ch != '0' && ch != '1') ch = getchar();
        for (int i = 1; i <= n; i++) b[i] = ch - '0', ch = getchar();
        ans = true;
        for (int i = 1; i <= c; i++) {
            flag = a[p[i - 1] + 1] == b[p[i - 1] + 1];
            for (int j = p[i - 1] + 1; j <= p[i]; j++) ans &= (flag == (a[j] == b[j]));
        }
        for (int i = p[c] + 1; i <= n; i++) ans &= (a[i] == b[i]);
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
