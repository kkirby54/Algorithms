#include <cstdio>
#include <algorithm>
#include <cstring>

int T, N;
int score[2][100001];
int dp[3][100001];

// state가 0이면 X
// state가 1이면 이전에 첫째 행을 뗐음
// state가 2이면 이전에 둘째 행을 뗐음
int sticker(int state, int curr) {
	// 종료 조건
	if (curr == N) return 0;

	int& ret = dp[state][curr];
	if (ret != -1) return ret;

	// 실제 계산
	ret = sticker(0, curr + 1);
	if (state != 1) {
		ret = std::max(ret, sticker(1, curr + 1) + score[0][curr]);
	}
	if (state != 2) {
		ret = std::max(ret, sticker(2, curr + 1) + score[1][curr]);
	}

	return ret;
}

int main() {
	scanf("%d", &T);
	
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);

		memset(dp, -1, sizeof(dp));
		
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &score[i][j]);
			}
		}

		printf("%d\n", sticker(0, 0));
	}

}