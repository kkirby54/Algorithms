#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int T, V, E, a, b, p, c;
int parent[10000];
vector<int> adj[10000];
int depth[10000];

void dfs(int curr) {
	for (int next : adj[curr]) {
		if (depth[next] == -1) {
			depth[next] = depth[curr] + 1;
			dfs(next);
		}
	}
}

int countSubtree(int curr) {

	int ret = 1;
	for (int next : adj[curr]) {
		ret += countSubtree(next);
	}
	return ret;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %d %d", &V, &E, &a, &b);
		a--; b--;
		memset(depth, -1, sizeof(depth));
		memset(parent, -1, sizeof(depth));
		for (int i = 0; i < V; i++) adj[i].clear();

		depth[0] = 0;
		for (int i = 0; i < E; i++) {
			scanf("%d %d", &p, &c);
			p--; c--;
			adj[p].push_back(c);
			parent[c] = p;
		}

		dfs(0);

		if (depth[a] < depth[b]) swap(a, b);

		while (depth[a] != depth[b]) {
			a = parent[a];
		}

		while (a != b) {
			a = parent[a];
			b = parent[b];
		}

		// 그리고 서브트리 개수를 세기
		int ret = countSubtree(a);

		printf("#%d %d %d\n", t, a + 1, ret);
	}

}