#include <cstdio>
#include <vector>
#include <queue>

int N, M, A, B, curr;

int indegree[32000] = { 0 };
std::vector<int> adj[32000];
std::queue<int> Q;

int main() {

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		adj[A - 1].push_back(B - 1);
		indegree[B - 1]++;
	}

	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) Q.push(i);
	}

	for (int i = 0; i < N; i++) {
		curr = Q.front();
		printf("%d ", curr + 1);
		Q.pop();

		for (int next : adj[curr]) {
			if (--indegree[next] == 0) Q.push(next);
		}

	}
}