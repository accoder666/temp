#include <cstdio>
#include <set>
using namespace std;

set<unsigned long long> S[2];

int main() {
    int k;
    scanf("%d", &k);
    S[0].insert(0);
    unsigned long long val = 1, tmp;
    for (int i = 0; i <= 18; i++) {
        S[(i & 1) ^ 1].clear();
        for (unsigned long long j : S[i & 1]) {
            if (!(j & ((unsigned long long)1 << i)))
                S[(i & 1) ^ 1].insert(j);
            tmp = j + val;
            if (tmp & ((unsigned long long)1 << i)) {
                S[(i & 1) ^ 1].insert(tmp);
                if (!(--k)) {
                    printf("%llu\n", tmp);
                    return 0;
                }
            }
        }
        val *= (unsigned long long)10;
    }
    printf("overflowed!!!\n");
    return 0;
}
