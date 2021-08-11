#include <cstdio>
using namespace std;

const int maxn = 10000010;
unsigned char S[maxn];

int main() {
    int n;
    scanf("%d %s", &n, S);
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n)
        if (S[(i + k) % n] == S[(j + k) % n])
            k++;
        else {
            if (S[(i + k) % n] > S[(j + k) % n])
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                j++;
            k = 0;
        }
    int ans = i < j ? i : j;
    for (int p = 0; p < n; p++) putchar(S[(p + ans) % n]);
    printf("\n");
    return 0;
}
