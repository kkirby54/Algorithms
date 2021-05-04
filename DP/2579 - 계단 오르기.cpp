#include <cstdio>
#include <algorithm>
#include <cstring>

int N, score[300];
int dp[300][3];

// state는 상태를 저장.
// 0이면 이전 X
// 1이면 한 계딴 등.
int stair(int curr, int state) {
	if (curr <= -1) return 0;
	
	int& ret = dp[curr][state];
	if (ret != -1) return ret;

	// 실제 계산
	
	// 두 번 뛴다

	ret = stair(curr - 2, 0) + score[curr];

	if (state != 1) {
		ret = std::max(ret, stair(curr - 1, state + 1) + score[curr]);
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", score + i);
	}

	memset(dp, -1, sizeof(dp));

	printf("%d", stair(N - 1, 0));

}