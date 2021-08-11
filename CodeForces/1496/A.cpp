#include <cstdio>
using namespace std;

const int maxn = 110;
char S[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k;
    bool flag;
    while (t--) {
        scanf("%d %d", &n, &k);
        scanf("%s", S + 1);
        if (!k) {
            printf("YES\n");
            continue;
        }
        if (n <= (k << 1)) {
            printf("NO\n");
            continue;
        }
        flag = true;
        for (int i = 1; i <= k; i++) flag &= (S[i] == S[n - i + 1]);
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;
}
