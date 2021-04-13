#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
	int N, K, cost[501], result[501] = { 0 };
	int indegree[501] = { 0 };
	std::vector<int> adj[501];

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &cost[i]);

		while (1) {
			scanf("%d", &K);
			if (K == -1) break;

			adj[K - 1].push_back(i);
			indegree[i]++;
		}
	}

	std::queue<int> Q;

	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) {
			Q.push(i);
			result[i] = cost[i];
		}
	}

	int curr;

	for (int i = 0; i < N; i++) {
		curr = Q.front();
		Q.pop();

		// 1을 거쳐서 가야 하는 애들에 대해서,
		for (auto next : adj[curr]) {
			// result[curr]과 cost[next]를 더한 그 총 합보다,
			// result[next]에 이미 더 큰 cost가 저장되어 있다고 하자 (다른 경로로 갱신 등으로)
			// 따라서 이미 저장된 result[next]가 result[curr] + cost[next]보다도 더 클 수 있기 때문에,
			// 아래와 같은 std::max를 써서 더 큰 값을 취한다.
			// 그래야지만 모든 간선을 고려한 최소건설시간이 나온다.
	
			result[next] = std::max(result[next], result[curr] + cost[next]);
			if (--indegree[next] == 0) Q.push(next);
		}
	}

	for (int i = 0; i < N; i++) {
		printf("%d\n", result[i]);
	}



	/*
	for (int i = 0; i < N; i++) {
		printf("%d에 대해 : ", i);
		for (int e : adj[i]) {
			printf("%d ", e);
		}
		printf(", indegree = %d\n", indegree[i]);
	}
	*/



}