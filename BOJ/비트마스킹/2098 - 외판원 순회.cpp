#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int MAX_V = 16;
const int INF = 987654321;

int N, final_state;
int matrix[MAX_V][MAX_V];
int dp[MAX_V][1 << MAX_V]; // 여기에 지금까지의 경로를 다 정해둔다.
						// N = 5라면, 0000 .... 0000 1 1111 이 되어야 함.

// pos번째 bit를 검사
int get(int curr, int pos) {
	return (1 & (curr >> pos));
}

// pos번째 bit를 1로 만든 결과를 반환
int set(int curr, int pos) {
	return (curr | (1 << pos));
}

int TSP(int currState, int prev, int cnt) {
	if (currState == final_state) {
		// 자 여기서 prev -> 0 으로 연결해야 한다.
		if (matrix[prev][0] == 0) return INF;
		return matrix[prev][0];
	}

	int& ret = dp[prev][currState];
	if (ret != -1) return ret;

	ret = INF;
	// prev에서 갈 수 있는 곳은?
	for (int i = 0; i < N; i++) {
		if (matrix[prev][i] == 0) continue;

		// 갈 수 있다면, 가고 표시한다.
		// 그 전에, 이미 방문한 곳이라면 갈 필요 없음.
		
		// 또한 시작점으로 돌아갈 때는
		// cnt, 즉 여기서는 간선이 정확히 N개여야 한다. (V0 -> V1 -> V2 -> .. -> Vn-1 -> V0)
		if (get(currState, i) && (cnt != N - 1))
			continue;

		int nextState = set(currState, i);
		
		// 그럼 next를 통해 가는 것이니까, prev->i를 잇는 weight를 더한다.
		ret = min(ret, TSP(nextState, i, cnt + 1) + matrix[prev][i]);
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	// 마지막 state 저장
	for (int i = 0; i < N; i++) {
		final_state = set(final_state, i);
	}
	memset(dp, -1, sizeof(dp));

	// 임의로 0에서 시작한다고 가정한다.
	printf("%d\n", TSP(1, 0, 0));

}