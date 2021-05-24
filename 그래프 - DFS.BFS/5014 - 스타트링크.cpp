#include <cstdio>
#include <queue>

bool visited[1000005];

int main() {
	int F, S, G, U, D;
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	
	// 총 F층
	// G로 가려함
	// 현재 S에.

	std::queue<int> Q;
	visited[S] = true;
	Q.push(S);
	int level = 0;

	while (!Q.empty()) {
		int qSize = Q.size();
		//printf("=====%d====\n", level);
		for (int i = 0; i < qSize; i++) {
			int curr = Q.front();
			Q.pop();

			if (curr == G) {
				printf("%d", level);
				return 0;
			}

			if (curr + U <= F && !visited[curr + U]){
				Q.push(curr + U);
				visited[curr + U] = true;
			}

			if (curr - D < 1 || visited[curr - D]) continue;
			Q.push(curr - D);
			visited[curr - D] = true;
		}
		level++;
	}
	printf("use the stairs");

}