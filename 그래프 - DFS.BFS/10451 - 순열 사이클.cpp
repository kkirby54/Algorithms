#include <cstdio>
#include <vector>
#include <algorithm>

int T, N, a;
int adj[1000];
bool visited[1000];

void dfs(int curr) {
	visited[curr] = true;
	if (!visited[adj[curr]]) dfs(adj[curr]);
}

int main() {
	scanf("%d", &T);
	
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		int cnt = 0;
		std::fill(visited, visited + N, false);

		for (int i = 0; i < N; i++) {
			scanf("%d", adj + i);
			adj[i]--;
		}

		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				dfs(i);
				cnt++;
			}
		}
		printf("%d\n", cnt);

	}

}