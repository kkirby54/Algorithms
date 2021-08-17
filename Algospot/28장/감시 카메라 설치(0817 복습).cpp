#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int C, G, H, u, v;
vector<int> adj[1000];
//vector<int> discovered;
bool visited[1000];
int ret;

const int INSTALLED = 2;
const int WATCHED = 1;
const int UNWATCHED = 0;

int dfs(int curr) {
	visited[curr] = true;

	int children[3] = { 0 };
	for (int next : adj[curr]) {
		if (visited[next]) continue;
		
		children[dfs(next)]++;
	}
	
	if (children[UNWATCHED]) {
		ret++;
		return INSTALLED;
	}
	else if (children[INSTALLED]) return WATCHED;
	return UNWATCHED;
}

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &G, &H);
		//discovered = vector<int>(G, -1);
		fill(visited, visited + G, false);
		for (int i = 0; i < G; i++) {
			adj[i].clear();
		}
		ret = 0;

		// 0 ~ g-1
		// h개의 복도
		for (int i = 0; i < H; i++) {
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		for (int i = 0; i < G; i++) {
			if (!visited[i] && dfs(i) == 0) {
				ret++;
			}
		}
		printf("%d\n", ret);
	}

}