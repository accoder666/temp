#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
char S[maxn];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", S);
        printf("%d\n", strlen(S));
    }
    return 0;
}
