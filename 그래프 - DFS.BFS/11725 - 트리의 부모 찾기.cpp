#include <cstdio>
#include <vector>
#include <algorithm>

int N, u, v;
std::vector<int> adj[100000];
int parent[100000];

void dfs(int curr) {

	for (int next : adj[curr]) {
		if (parent[next] == -1) {
			parent[next] = curr;
			dfs(next);
		}
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N-1; i++) {
		scanf("%d %d", &u, &v);
		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}

	std::fill(parent, parent + N, -1);
	dfs(0);

	for (int i = 1; i < N; i++) {
		printf("%d\n", parent[i] + 1);
	}

}