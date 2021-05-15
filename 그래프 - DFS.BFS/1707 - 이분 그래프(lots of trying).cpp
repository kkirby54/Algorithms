#include <cstdio>
#include <algorithm>
#include <vector>

int K, V, E, u, v;
std::vector<int> adj[20000];
int map[20000];
bool isPossible = true;

void dfs(int curr) {
	
	for (int next : adj[curr]) {
		if (map[next] == map[curr]) {
			isPossible = false;
			return;
		}

		if (map[next] == 0) {
			if (map[curr] == 1) map[next] = 2;
			else if (map[curr] == 2) map[next] = 1;
			dfs(next);
		}
	}
}

int main() {
	scanf("%d", &K);

	for (int t = 0; t < K; t++) {
		scanf("%d %d", &V, &E);

		for (int i = 0; i < V; i++)
			adj[i].clear();
		std::fill(map, map + V, 0);
		isPossible = true;

		for (int i = 0; i < E; i++) {
			scanf("%d %d", &u, &v);
			u--; v--;
			adj[v].push_back(u);
			adj[u].push_back(v);
		}
		
		for (int i = 1; i < V; i++) {
			if (map[i] == 0) {
				map[i] = 1;
				dfs(i);
			}
		}

		/*
		puts("\n=====");
		for (int i = 0; i < V; i++)
			printf("%d ", map[i]);
		puts("\n=====");
		*/

		if (isPossible) puts("YES");
		else puts("NO");

	}


}