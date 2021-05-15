#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>

int N, M, V, a,b;
bool visited[1001];
std::vector<int> adj[1001];

void dfs(int curr) {
	visited[curr] = true;

	printf("%d ", curr);
	for (int next : adj[curr]) {
		if (!visited[next])
			dfs(next);
	}

}

int main() {
	scanf("%d %d %d", &N, &M, &V);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// dfs
	for (int i = 1; i <= N; i++) {
		std::sort(adj[i].begin(), adj[i].end());
	}
	dfs(V);
	puts("");

	// bfs
	std::fill(visited, visited + N + 1, false);
	std::queue<int> Q;
	Q.push(V);
	visited[V] = true;

	while (!Q.empty()) {
		int curr = Q.front();
		Q.pop();

		printf("%d ", curr);

		for (int next : adj[curr]) {
			if (!visited[next]) {
				Q.push(next);
				visited[next] = true;
			}
		}

	}

}