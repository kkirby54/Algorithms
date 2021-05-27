#include <cstdio>
#include <vector>
#include <cstring>

int N, towns[10000];
int A, B;
std::vector<int> adj[10000];
std::vector<int> tree[10000];

bool visited[10000];
int dp[10000][2];

void make_tree(int curr) {
	visited[curr] = true;

	for (int next : adj[curr]) {
		if (!visited[next]) {
			tree[curr].push_back(next);
			make_tree(next);
		}
	}
}

// state가 0이면 우수 X
// state가 1이면 우수
int perfect_town(int curr, bool state) {
	int& ret = dp[curr][state];
	if (ret != -1) return ret;

	// 고르는 세계, 안 고르는 세계
	int pick = 0, notpick = 0;

	if (!state) {
		pick = towns[curr];
		for (int next : tree[curr]) {
			pick += perfect_town(next, 1);
		}
	}
	
	for (int next : tree[curr]) {
		notpick += perfect_town(next, 0);
	}

	return ret = std::max(pick, notpick);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", towns + i);
	}
	
	memset(dp, -1, sizeof(dp));

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &A, &B);
		A--; B--;

		adj[A].push_back(B);
		adj[B].push_back(A);
	}

	make_tree(0);

	printf("%d", perfect_town(0, 0));

}