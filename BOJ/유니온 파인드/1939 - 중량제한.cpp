#include <cstdio>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;
typedef pair<int, int> P;

int N, M, A, B, C;
P edges[100000];
int parent[10000];

int find(int curr){
    if (parent[curr] == -1) return curr;
    return parent[curr] = find(parent[curr]);
}

void mergeFunc(int u, int v){
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV){
        parent[rootU] = rootV;
    }
}


int main() {
    memset(parent, -1, sizeof(parent));

    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &A, &B, &C);
        A--; B--;

        edges[i] = P(C, A * 10000 + B);
    }

    int S, D;
    scanf("%d %d", &S, &D);

    // C 높은 걸로 정렬
    std::sort(edges, edges + M, std::greater<P>());

    for (int i = 0; i < M; i++){
        int currDist = edges[i].first;
        int n1 = edges[i].second / 10000;
        int n2 = edges[i].second % 10000;

        // n1과 n2를 merge한다.
        mergeFunc(n1, n2);

        if (find(S-1) == find(D-1)){
            printf("%d\n", currDist);
            break;
        }
    }

}