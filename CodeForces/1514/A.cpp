#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n, a;
    bool flag;
    while (t--) {
        flag = true;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            if (roundl(sqrtl(a)) * roundl(sqrtl(a)) != a)
                flag = false;
        }
        printf(flag ? "NO\n" : "YES\n");
    }
    return 0;
}
