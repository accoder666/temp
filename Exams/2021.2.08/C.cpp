#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const long long mod = 1000000007;
const int maxn = 200, sigma_size = 26;
int trie[maxn][sigma_size], fail[maxn], cnt;
bool flag[maxn];
char S[maxn];
queue<int> Q;
inline long long inv(long long);
long long A[maxn][maxn];

int main() {
    freopen("substring.in", "r", stdin);
    freopen("substring.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int n;
    int len, u;
    long long c;
    while (t--) {
        scanf("%d", &n);
        memset(trie, 0, sizeof(trie));
        memset(fail, 0, sizeof(fail));
        memset(flag, false, sizeof(flag));
        memset(A, 0, sizeof(A));
        cnt = 0;
        while (n--) {
            scanf("%s", S);
            len = strlen(S), u = 0;
            for (int i = 0; i < len; i++) {
                if (!trie[u][S[i] - 'a'])
                    trie[u][S[i] - 'a'] = ++cnt;
                u = trie[u][S[i] - 'a'];
            }
            flag[u] = true;
        }
        for (int i = 0; i < sigma_size; i++)
            if (trie[0][i])
                Q.push(trie[0][i]);
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < sigma_size; i++)
                if (trie[u][i])
                    fail[trie[u][i]] = trie[fail[u]][i], Q.push(trie[u][i]);
                else
                    trie[u][i] = trie[fail[u]][i];
        }
        c = mod - inv(sigma_size);
        for (int i = 0; i <= cnt; i++)
            if (flag[i])
                A[i][i] = 1;
            else {
                for (int j = 0; j < sigma_size; j++) A[i][trie[i][j]] = (A[i][trie[i][j]] + c) % mod;
                A[i][i]++, A[i][cnt + 1] = 1;
            }
        for (int i = 0; i <= cnt; i++) {
            int r = i;
            for (int j = i; j <= cnt; j++)
                if (A[j][i]) {
                    r = j;
                    break;
                }
            if (i != r)
                for (int j = 0; j <= cnt + 1; j++) A[r][j] ^= A[i][j] ^= A[r][j] ^= A[i][j];
            c = inv(A[i][i]);
            for (int j = cnt + 1; j > i; j--)
                for (int k = i + 1; k <= cnt; k++) A[k][j] = (A[k][j] - A[k][i] * c % mod * A[i][j]) % mod;
        }
        for (int i = cnt; i >= 0; i--) {
            for (int j = i + 1; j <= cnt; j++)
                A[i][cnt + 1] = (A[i][cnt + 1] - A[j][cnt + 1] * A[i][j]) % mod;
            A[i][cnt + 1] = A[i][cnt + 1] * inv(A[i][i]) % mod;
        }
        printf("%lld\n", (A[0][cnt + 1] + mod) % mod);
    }
    return 0;
}

inline long long inv(long long v) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * v % mod;
        v = v * v % mod, e >>= 1;
    }
    return ret;
}
