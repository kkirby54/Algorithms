#include <cstdio>
#include <algorithm>

int T, N, cnt;

int arr[100000];
bool visited[100000], finished[100000];

// 사이클을 찾기.

void dfs(int curr) {
	visited[curr] = true;
	int next = arr[curr];

	if (visited[next]) {
		if (!finished[next]) {
			// next부터 다시 돌면서 curr에 올때까지.
			for (int tmp = next; tmp != curr; tmp = arr[tmp])
				cnt++;
			cnt++;
		}
	}
	else {
		dfs(next);
	}
	finished[curr] = true;
}

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		
		cnt = 0;
		std::fill(visited, visited + N, false);
		std::fill(finished, finished + N, false);

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);
			arr[i]--;
		}

		for (int i = 0; i < N; i++) {
			if (!visited[i]) dfs(i);
		}

		printf("%d\n", N - cnt);
	}


}