#include <cstdio>
using namespace std;

const int maxn = 1010;
int s[maxn];

int main() {
    int T;
    scanf("%d", &T);
    int n, a, t;
    while (T--) {
        scanf("%d", &n);
        t = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            if (a == 1)
                s[++t] = 1;
            else {
                while (t && s[t] != a - 1) t--;
                s[t]++;
            }
            for (int j = 1; j < t; j++) printf("%d.", s[j]);
            printf("%d\n", s[t]);
        }
    }
    return 0;
}
