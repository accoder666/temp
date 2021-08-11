#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 400010;
vector<int> check_validity(const int&, vector<int>, vector<int>, vector<int>, vector<int>, vector<int>,
                           vector<int>);

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    vector<int> X(m), Y(m), S(q), E(q), L(q), R(q);
    for (int i = 0; i < m; i++) scanf("%d %d", &X[i], &Y[i]);
    for (int i = 0; i < q; ++i) scanf("%d %d %d %d", &S[i], &E[i], &L[i], &R[i]);
    vector<int> A = check_validity(n, X, Y, S, E, L, R);
    for (int i : A) printf("%d\n", i);
    return 0;
}

struct edge {
    int from, to;
};
edge G[maxn << 1];
int head[maxn], cnt;

vector<int> check_validity(const int& N, vector<int> X, vector<int> Y, vector<int> S, vector<int> E,
                           vector<int> L, vector<int> R) {
    int M = X.size(), Q = S.size();
    for (int i = 0; i < M; i++) {
    }
    vector<int> A(Q);
    for (int& i : A) i = 0;
    return A;
}
