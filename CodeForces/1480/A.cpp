#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100;
char S[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int len;
    while (t--) {
        scanf("%s", S);
        len = strlen(S);
        for (int i = 0; i < len; i++)
            if (i & 1)
                putchar(S[i] == 'z' ? 'y' : 'z');
            else
                putchar(S[i] == 'a' ? 'b' : 'a');
        printf("\n");
    }
    return 0;
}
