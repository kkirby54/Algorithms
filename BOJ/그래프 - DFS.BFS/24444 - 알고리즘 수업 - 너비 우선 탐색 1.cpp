#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

int N, M, R;
int visited[100000];
int u, v;
std::vector<int> adj[100000];

int cnt = 0;

int main(){
    scanf("%d %d %d", &N, &M, &R);

    for (int i = 0; i < M; i++){
        scanf("%d %d", &u, &v);
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    for (int i = 0; i < N; i++){
        std::sort(adj[i].begin(), adj[i].end());
    }

    std::queue<int> Q;
    Q.push(R-1);
    visited[R-1] = ++cnt;

    while (!Q.empty()){
        int curr = Q.front();
        Q.pop();

        for (int next : adj[curr]){
            if (visited[next]) continue;
            Q.push(next);
            visited[next] = ++cnt;
        }
    }

    for (int i = 0; i < N; i++){
        printf("%d\n", visited[i]);
    }

}