#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    int x, y;
    while (t--) {
        scanf("%d %d", &x, &y);
        printf("%d %d\n", x - 1, y);
    }
    return 0;
}
