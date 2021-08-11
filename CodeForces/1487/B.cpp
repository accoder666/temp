#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n, k;
    while (t--) {
        scanf("%d %d", &n, &k);
        if (n & 1) {
            if (n == 3)
                printf("%d\n", ((k - 1) << 1) % n + 1);
            else
                printf("%d\n", (k - 1 + (k - 1) / (n >> 1)) % n + 1);
        } else
            printf("%d\n", (k - 1) % n + 1);
    }
    return 0;
}
