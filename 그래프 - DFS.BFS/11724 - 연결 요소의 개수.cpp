#include <cstdio>
#include <algorithm>
#include <vector>

int N, M, cnt, a,b;
bool visited[1001];
std::vector<int> adj[1001];

void dfs(int curr) {
	visited[curr] = true;

	for (int next : adj[curr]) {
		if (!visited[next])
			dfs(next);
	}

}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {
			cnt++;
			dfs(i);
		}
	}
	printf("%d", cnt);
}