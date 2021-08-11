#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 300010;
char s[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int len, p;
    while (t--) {
        scanf("%s", s);
        len = strlen(s);
        p = -1;
        for (int i = 0; i < len; i++)
            if (s[i] != 'a') {
                p = i;
                break;
            }
        if (p == -1)
            printf("NO\n");
        else {
            printf("YES\n");
            for (int i = 0; i < len - p; i++) putchar(s[i]);
            putchar('a');
            for (int i = len - p; i < len; i++) putchar(s[i]);
            putchar('\n');
        }
    }
    return 0;
}
