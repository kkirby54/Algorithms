#include <cstdio>
#include <queue>
#include <vector>

int main() {
	int N, M, K, prev, next;
	std::vector<int> adj[1001];
	int indegree[1001] = { 0 };

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) {
		scanf("%d", &K);

		// 일단 제일 처음은 얌전하게 받는다.
		scanf("%d", &prev);
		for (int i = 0; i < K - 1; i++) {
			scanf("%d", &next);
			adj[prev - 1].push_back(next - 1);

			// 들어오는 간선을 표시해야 한다.
			// prev -> next로 가기 때문에,
			// indegree[next]++
			indegree[next - 1]++;
			
			// 그 후 지금 next 값을 prev에 넣는다.
			prev = next;
		}
	}

	// 위상정렬 -> 들어오는 간선이 없는 정점을 큐에 넣는다.
	std::queue<int> Q;

	for (int i = 0; i < N; i++) {
		if (!indegree[i]) Q.push(i);
	}

	// 이제 N번 돌면서(가수가 N명이니까)
	// 큐를 뺀다.
	// 뺀 정점에서 연결된 간선을 제거한다.

	int result[1001];

	for (int i = 0; i < N; i++) {
		if (Q.empty()) {
			printf("0");
			return 0;
		}

		int curr = Q.front();
		result[i] = curr;
		Q.pop();

		for (int e : adj[curr]) {
			if (--indegree[e] == 0) Q.push(e);
		}
	}

	for (int i = 0; i < N; i++) {
		printf("%d\n", result[i] + 1);
	}

}