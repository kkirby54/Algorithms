#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>

int N, K, level, curr;
bool visited[100001];

int main() {
	scanf("%d %d", &N, &K);

	std::queue<int> Q;
	Q.push(N);
	visited[N] = true;

	while (!Q.empty()) {
		int qSize = Q.size();

		//printf("=====%d=====\n", level);
		for (int i = 0; i < qSize; i++) {
			curr = Q.front();
			Q.pop();

			if (curr == K) {
				printf("%d", level);
				return 0;
			}

			if (curr * 2 <= 100000 && !visited[curr * 2]) {
				visited[curr * 2] = true;
				Q.push(curr * 2);
			}
			if (0 <= curr - 1 && curr - 1 <= 100000 &&
				!visited[curr - 1]) {
				visited[curr - 1] = true;
				Q.push(curr - 1);
			}
			if (curr + 1 <= 100000 &&
				!visited[curr + 1]) {
				visited[curr + 1] = true;
				Q.push(curr + 1);
			}
		}
		level++;
	}


}