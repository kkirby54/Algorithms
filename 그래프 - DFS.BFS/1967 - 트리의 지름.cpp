#include <cstdio>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;

int N, u, v, c;
int curr_max;
int far_node;

std::vector<P> adj[10000];
bool visited[10000];

int dfs(int curr, int distance) {
	visited[curr] = true;

	if (distance > curr_max) {
		curr_max = distance;
		far_node = curr;
	}

	int ret = 0;

	for (auto P : adj[curr]) {
		int next = P.first, dist = P.second;

		if (!visited[next]) {
			ret = std::max(ret, dfs(next, distance + dist) + dist);
		}
	}
	return ret;
}


int main() {
	scanf("%d", &N);

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d %d", &u, &v, &c);
		adj[u - 1].push_back(P(v - 1, c));
		adj[v - 1].push_back(P(u - 1, c));
	}

	dfs(0, 0);

	std::fill(visited, visited + N, false);
	
	printf("%d", dfs(far_node, 0));
}