#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
bool flag[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int q, d, a;
    while (t--) {
        scanf("%d %d", &q, &d);
        memset(flag, false, sizeof(flag));
        flag[0] = true;
        for (int i = 1; i < 11 * d; i++)
            for (int j = 1; j <= i; j++)
                if ((j % 10 == d || j / 10 == d) && flag[i - j])
                    flag[i] = true;
        while (q--) {
            scanf("%d", &a);
            if (a >= 11 * d || flag[a])
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
