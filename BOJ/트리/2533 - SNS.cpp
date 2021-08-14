#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_N = 1000000;

int N, u, v;
vector<int> adj[MAX_N];
vector<int> tree[MAX_N];
bool visited[MAX_N];

int dp[MAX_N + 1][2];

void dfs(int curr) {
	visited[curr] = true;
	for (int next : adj[curr]) {
		if (!visited[next]) {
			tree[curr].push_back(next);
			dfs(next);
		}
	}
}

int SNS(int curr, bool prev) {
	int& ret = dp[curr][prev];
	if (ret != -1) return ret;

	int notpick = 987654321, pick = 1;

	for (int next : tree[curr]) {
		pick += SNS(next, true);
	}

	if (prev) {
		notpick = 0;
		for (int next : tree[curr]) {
			notpick += SNS(next, false);
		}
	}

	// 이전 애가 얼리어답터면, 얜 얼리어답터일 수도 아닐 수도, pick notpick

	return ret = min(notpick, pick);
}


int main() {
	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0);

	printf("%d\n", SNS(0, true));


}