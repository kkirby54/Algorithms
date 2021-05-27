#include <cstdio>
#include <vector>
#include <algorithm>

int N, R, Q, U, V, tmp;
std::vector<int> adj[100005];
std::vector<int> tree[100005];
bool visited[100005];
int dp[100005];

void make_tree(int curr) {
	// curr의 인접한 애들을 다 봐.
	dp[curr] = 1;
	visited[curr] = true;

	for (int next : adj[curr]) {
		if (!visited[next]) {
			tree[curr].push_back(next);
			make_tree(next);
		}
	}
}

int subtree_nums(int curr) {
	int& ret = dp[curr];
	if (ret != -1) return ret;

	// 부분문제로 정의하자면,
	// dp[next] + 1
	ret = 1;
	for (int next : tree[curr]) {
		ret += subtree_nums(next);
	}

	return ret;
}

int main() {
	scanf("%d %d %d", &N, &R, &Q);

	for (int i = 0; i < N-1; i++) {
		scanf("%d %d", &U, &V);
		adj[U].push_back(V);
		adj[V].push_back(U);
	}

	std::fill(dp, dp + N + 5, -1);

	// 먼저 그래프를 트리화한다.
	make_tree(R);

	/*
	printf("===============\n");
	for (int i = 1; i <= N; i++) {
		printf("%d의 인접한 애들 : ", i);
		for (int e : tree[i]) {
			printf("%d, ", e);
		}
		puts("");
	}
	printf("===============\n\n");
	*/

	subtree_nums(R);


	for (int i = 0; i < Q; i++) {
		scanf("%d", &tmp);
		printf("%d\n", dp[tmp]);
	}



}