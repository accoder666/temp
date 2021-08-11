#include <cstdio>
#include <cstring>
using namespace std;

const int maxw = 10010, maxt = 1000010;
char W[maxw], T[maxt];
int nxt[maxw];

int main() {
    int t;
    scanf("%d", &t);
    int lenw, lent, ans;
    while (t--) {
        scanf("%s %s", W, T);
        lenw = strlen(W), lent = strlen(T);
        memset(nxt, 0, sizeof(nxt));
        for (int i = 1, j = 0; i <= lenw; i++) {
            while (j && W[i] != W[j]) j = nxt[j];
            if (W[i] == W[j])
                j++;
            nxt[i + 1] = j;
        }
        ans = 0;
        for (int i = 0, j = 0; i <= lent; i++) {
            while (j && T[i] != W[j]) j = nxt[j];
            if (T[i] == W[j])
                j++;
            if (j == lenw)
                ans++, j = nxt[j];
        }
        printf("%d\n", ans);
    }
    return 0;
}
