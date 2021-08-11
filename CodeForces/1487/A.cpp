#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n, a, m, c;
    while (t--) {
        scanf("%d", &n);
        c = 0, m = 101;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            if (a == m)
                c++;
            else if (a < m)
                m = a, c = 1;
        }
        printf("%d\n", n - c);
    }
    return 0;
}
