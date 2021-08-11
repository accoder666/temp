#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int c;
    while (t--) {
        scanf("%d", &n);
        c = 9;
        printf("%d", c), c = (c + 9) % 10;
        for (int i = 2; i <= n; i++) printf("%d", c), c = (c + 1) % 10;
        printf("\n");
    }
    return 0;
}
