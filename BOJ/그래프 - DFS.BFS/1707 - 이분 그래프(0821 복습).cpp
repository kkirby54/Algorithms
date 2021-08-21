#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int K, V, E;
int u, v;

vector<int> adj[20000];
bool visited[20000];
int val[20000];
bool isPossible = true;

void dfs(int curr, int prev) {
	visited[curr] = true;
	val[curr] = val[prev] == 0 ? 1 : 0;
	for (int next : adj[curr]) {
		if (!visited[next]) {
			dfs(next, curr);
		}
		else {
			if (val[next] == val[curr]) {
				isPossible = false;
				break;
			}
		}
	}
}

int main() {
	scanf("%d", &K);
	while (K--) {
		scanf("%d %d", &V, &E);
		for (int i = 0; i < V; i++) adj[i].clear();
		fill(visited, visited + V, false);
		fill(val, val + V, 0);
		isPossible = true;


		for (int i = 0; i < E; i++) {
			scanf("%d %d", &u, &v);
			u--; v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		for (int i = 0; i < V; i++) {
			if (!visited[i])
				dfs(i, 0);
		}


		if (!isPossible) puts("NO");
		else puts("YES");

	}

}