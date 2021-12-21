#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 987654321;

bool visited[10000];
int N, w[10000], u, v;
vector<int> adj[10000];
vector<int> tree[10000];
int dp[10001][2];

void dfs(int curr) {
	visited[curr] = true;
	for (int next : adj[curr]) {
		if (!visited[next]) {
			tree[curr].push_back(next);
			dfs(next);
		}
	}
}

int treeDP(int curr, bool prev) {
	int& ret = dp[curr][prev];
	if (ret != -1) return ret;

	// prev가 true라면 무조건 false
	// prev가 false라면, false일수도, true일 수도.

	int notpick = 0;
	int pick = -INF;
	if (!prev) {
		pick = w[curr];
		for (int next : tree[curr]) {
			pick += treeDP(next, true);
		}
	}

	for (int next : tree[curr]) {
		notpick += treeDP(next, false);
	}
	return ret = max(notpick, pick);
}

vector<int> result;
void trackAnswer(int curr, bool prev) {
	int notpick = 0;
	int pick = -INF;

	if (!prev) {
		pick = w[curr];
		for (int next : tree[curr]) {
			pick += treeDP(next, true);
		}
	}
	for (int next : tree[curr]) {
		notpick += treeDP(next, false);
	}

	if (treeDP(curr, prev) == pick) {
		result.push_back(curr);
		for (int next : tree[curr])
			trackAnswer(next, true);
	}
	else {
		for (int next : tree[curr]) {
			trackAnswer(next, false);
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", w + i);
	}

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0);

	memset(dp, -1, sizeof(dp));

	printf("%d\n", treeDP(0, false));
	trackAnswer(0, false);
	std::sort(result.begin(), result.end());
	for (int e : result) {
		printf("%d ", e + 1);
	}
}

