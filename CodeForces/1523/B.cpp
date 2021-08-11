#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    int n;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%*d");
        printf("%d\n", 3 * n);
        for (int i = 1; i <= n; i += 2)
            printf("1 %d %d\n2 %d %d\n1 %d %d\n1 %d %d\n2 %d %d\n1 %d %d\n", i, i + 1, i, i + 1, i, i + 1, i,
                   i + 1, i, i + 1, i, i + 1);
    }
    return 0;
}
