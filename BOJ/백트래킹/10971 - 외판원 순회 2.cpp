#include <cstdio>
#include <algorithm>
const int INF = 987654321;

int N, W[10][10];
int start = 0;
bool visited[10];

int sales(int curr, int cnt) {
	if (cnt == N) {
		// curr과 start가 이어져있지 않으면 INF,
		// 이어져있다면 정상값.
		return W[curr][start] == 0 ? INF : W[curr][start];
	}

	int ret = INF;
	// 가능한 모든 곳을 다 방문해본다.
	// 방문 표시를 하고, 이동
	for (int i = 0; i < N; i++) {
		if (visited[i]) continue;
		if (W[curr][i] == 0) continue;

		visited[i] = true;
		ret = std::min(ret, W[curr][i] + sales(i, cnt + 1));
		visited[i] = false;
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &W[i][j]);
		}
	}

	// 0에서 시작한다고 하자.
	visited[0] = true;
	int ret = sales(0, 1);
	printf("%d\n", ret);
}