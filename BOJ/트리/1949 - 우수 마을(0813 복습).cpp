#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int N, u, v;
int people[10000];
vector<int> adj[10000];
vector<int> tree[10000];
bool visited[10000];

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

int goodTown(int curr, bool prevGood) {
	int& ret = dp[curr][prevGood];
	if (ret != -1) return ret;

	int notpick = 0;
	int pick = 0;

	// 마을의 총 합.
	// 이전이 좋은 마을이었으면 여긴 안됨.
	for (int next : tree[curr]) {
		notpick += goodTown(next, false);
	}
	// 이전이 좋은 마을 아니었다면, 택해도 됨.
	if (!prevGood) {
		pick = people[curr];
		for (int next : tree[curr]) {
			pick += goodTown(next, true);
		}
	}

	return ret = max(pick, notpick);
}


int main() {
	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N; i++) scanf("%d", people + i);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// 그냥 0부터 시작하는 트리를 만들기?
	dfs(0);

	printf("답: %d\n", goodTown(0, false));


}