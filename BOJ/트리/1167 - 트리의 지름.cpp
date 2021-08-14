#include <cstdio>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> P;

int V, u, v, c;
std::vector<P> adj[100000];
bool visited[100000];
int go[100000];

int dfs(int curr) {
	visited[curr] = true;
	int ret = 0;

	for (auto e : adj[curr]) {
		int next = e.first, dist = e.second;
		if (!visited[next]) {
			int tmp = dfs(next) + dist;
			if (ret < tmp) {
				ret = tmp;
				go[curr] = next;
			}

		}
	}

	return ret;
}

int main() {
	scanf("%d", &V);
	for (int i = 0; i < V; i++) {
		scanf("%d", &u);
		while (1) {
			scanf("%d", &v);
			if (v == -1) break;
			scanf("%d", &c);

			adj[u - 1].push_back(P(v - 1, c));
		}
	}
	
	std::fill(go, go + V, -1);
	dfs(0);

	int far_node = 0;
	while (go[far_node] != -1) {
		far_node = go[far_node];
	}

	std::fill(visited, visited + V, false);
	printf("%d", dfs(far_node));
}