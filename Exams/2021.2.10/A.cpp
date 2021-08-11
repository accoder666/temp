#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, m, x1, y1, x2, y2;
    scanf("%d %d %d %d %d %d", &n, &m, &x1, &y1, &x2, &y2);
    if (abs(x1 - x2) + abs(y1 - y2) == 1)
        printf("-1\n");
    else if ((n <= 2 && m <= 2) || (n <= 3 && m <= 3 && x2 == 2 && y2 == 2))
        printf("1\n");
    else if ((n == 1 || m == 1 || (n == 2 && abs(y1 - y2) > 1) || (m == 2 && abs(x1 - x2) > 1) ||
              (abs(x1 - x2) + abs(y1 - y2) != 2 && (x2 <= 2 || x2 >= n - 1) && (y2 <= 2 || y2 >= m - 1))) ||
             (n == 3 && m == 3 && (x2 == 1 || x2 == 3) && (y2 == 1 || y2 == 3) && x1 == 2 && y1 == 2) ||
             (n == 3 && m == 3 && ((x1 == 2 && y1 != 2) || (x1 != 2 && y1 == 2))))
        printf("2\n");
    else
        printf("3\n");
    return 0;
}
