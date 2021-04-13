#include <cstdio>
#include <vector>
#include <queue>

int main() {
	int T, N, K, X, Y, W, curr;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		int indegree[1000] = { 0 };
		int result[1000] = { 0 };
		int time[1000];
		std::vector<int> adj[1000];
		std::queue<int> Q;

		scanf("%d %d", &N, &K);

		for (int i = 0; i < N; i++) {
			scanf("%d", &time[i]);
		}

		for (int i = 0; i < K; i++) {
			scanf("%d %d", &X, &Y);
			adj[X - 1].push_back(Y - 1);
			indegree[Y - 1]++;
		}

		scanf("%d", &W);

		// 정점을 돌면서 indegree가 0이라면,
		// Q에 넣고, result배열에 갱신한다.
		for (int i = 0; i < N; i++) {
			if (indegree[i] == 0) {
				Q.push(i);
				result[i] = time[i];
			}
		}

		// N개 정점만큼 반복한다.
		for (int i = 0; i < N; i++) {
			curr = Q.front();
			Q.pop();

			for (int next : adj[curr]) {
				if (--indegree[next] == 0)
					Q.push(next);
				result[next] = std::max(result[next], result[curr] + time[next]);
			}

		}

		printf("%d\n", result[W - 1]);

	}

}
[출처] 백준 1005. ACM Craft | 작성자 김꺼비

