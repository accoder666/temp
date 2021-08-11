#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010;
char S[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int x, y, len;
    int dx1, dx2, dy1, dy2;
    while (t--) {
        scanf("%d %d", &x, &y);
        scanf("%s", S);
        len = strlen(S);
        dx1 = dx2 = dy1 = dy2 = 0;
        for (int i = 0; i < len; i++) switch (S[i]) {
                case 'U':
                    dy1++;
                    break;
                case 'D':
                    dy2++;
                    break;
                case 'R':
                    dx1++;
                    break;
                case 'L':
                    dx2++;
                    break;
                default:
                    break;
            }
        printf((x > 0 ? dx1 >= x : dx2 >= -x) && (y > 0 ? dy1 >= y : dy2 >= -y) ? "YES\n" : "NO\n");
    }
    return 0;
}
