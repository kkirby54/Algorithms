#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int T, N;
int adj[100000];
bool visited[100000], finished[100000];
int cnt = 0;

void dfs(int curr) {
	visited[curr] = true;

	int next = adj[curr];
	if (!visited[next]) {
		dfs(next);
	}
	else {
		// 끝나지 않았다면, next - curr - next는 사이클을 이룬다. (역방향 간선)
		// curr이 먼저 발견됐고, dfs(curr)이 dfs(next)를 호출.
		if (!finished[next]) {
			int temp = curr;
			// 다시 curr로 돌아올 때까지 센다.
			do {
				cnt++;
				temp = adj[temp];
			} while (temp != curr);
		}

	}
	finished[curr] = true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", adj + i);
			adj[i]--;
		}
		fill(visited, visited + N, false);
		fill(finished, finished + N, false);

		cnt = 0;
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				dfs(i);
			}
		}

		printf("%d\n", N - (cnt));
	}

}