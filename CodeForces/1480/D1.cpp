#include <cstdio>
#include <unordered_map>
using namespace std;

const int maxn = 100010;
unordered_map<int, int> M;
int nxt[maxn], s[2][maxn];
int a[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (M.count(a[i]))
            nxt[M[a[i]]] = i, M[a[i]] = i;
        M[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (!nxt[i])
            nxt[i] = n + 1;
        printf("%d ", nxt[i]);
    }
    printf("\n");
    for (int i = 1; i <= n; i++)
        if (a[s[0][s[0][0]]] != a[i] && a[s[1][s[1][0]]] != a[i]) {
            if (nxt[a[s[0][s[0][0]]]] < nxt[a[s[1][s[1][0]]]])
                s[0][++s[0][0]] = i;
            else
                s[1][++s[1][0]] = i;
        } else if (a[s[0][s[0][0]]] != a[i])
            s[0][++s[0][0]] = i;
        else if (a[s[1][s[1][0]]] != a[i])
            s[1][++s[1][0]] = i;
    printf("%d\n", s[0][0] + s[1][0]);
    for (int i = 1; i <= s[0][0]; i++) printf("%d ", a[s[0][i]]);
    printf("\n");
    for (int i = 1; i <= s[1][0]; i++) printf("%d ", a[s[1][i]]);
    printf("\n");
    return 0;
}
