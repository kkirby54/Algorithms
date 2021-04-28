#include <cstdio>
#include <queue>
#include <algorithm>
#include <stack>

int N, K;
bool visited[100005];
int prev[100005];

int main() {
	// N에 있음 -> K로 이동
	scanf("%d %d", &N, &K);

	std::queue<int> Q;
	Q.push(N);
	visited[N] = true;

	int level = 0;
	int curr;
	while (!Q.empty()) {

		int qSize = Q.size();
		//printf("=====level : %d=====\n", level);
		for (int i = 0; i < qSize; i++) {
			curr = Q.front();
			Q.pop();

			if (curr == K) {
				printf("%d\n", level);
				break;
			}

			if (curr - 1 >= 0 && curr - 1 <= 100000 && !visited[curr - 1]) {
				Q.push(curr - 1);
				prev[curr - 1] = curr;
				visited[curr - 1] = true;
			}
			if (0 <= curr + 1 && curr + 1 <= 100000 && !visited[curr + 1]) {
				Q.push(curr + 1);
				prev[curr + 1] = curr;
				visited[curr + 1] = true;
			}
			if (0 <= curr * 2 && curr * 2 <= 100000 && !visited[curr * 2]) {
				Q.push(curr * 2);
				prev[curr * 2] = curr;
				visited[curr * 2] = true;
			}

		}
		if (curr == K) break;
		level++;
	}

	std::stack<int> s;

	for (int i = 0; i <= level; i++) {
		s.push(curr);
		curr = prev[curr];
	}

	while (!s.empty()) {
		printf("%d ", s.top());
		s.pop();
	}

}