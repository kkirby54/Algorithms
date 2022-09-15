#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, R;
int u, v;
vector<int> adj[100000];
int visited[100000];

int cnt = 0;
void dfs(int curr) {
	visited[curr] = ++cnt;
	
	for (int next : adj[curr]) {
		if (visited[next]) continue;
		dfs(next);
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &R);

	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}
	for (int i = 0; i < N; i++) {
		std::sort(adj[i].begin(), adj[i].end());
	}

	dfs(R - 1);

	for (int i = 0; i < N; i++) {
		printf("%d\n", visited[i]);
	}

}