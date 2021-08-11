#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool flag;
    while (t--) {
        flag = false;
        scanf("%d", &n);
        for (int i = 1; i <= 30; i++)
            if (!(n & ((1 << i) - 1)) &&
                (int)roundl(sqrtl(n >> i)) * (int)roundl(sqrtl(n >> i)) == (n >> i)) {
                printf("YES\n");
                flag = true;
                break;
            }
        if (!flag)
            printf("NO\n");
    }
    return 0;
}
