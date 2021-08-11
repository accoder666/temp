#include <cstdio>
using namespace std;

const int maxn = 100010;

int main() {
    int t;
    scanf("%d", &t);
    int r, b, d;
    while (t--) {
        scanf("%d %d %d", &r, &b, &d);
        printf((r && b && (r - b < 0 ? b - r : r - b) <= (d + 1) * (r < b ? r : b)) ? "YES\n" : "NO\n");
    }
    return 0;
}
