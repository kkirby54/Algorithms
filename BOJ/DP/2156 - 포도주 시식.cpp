#include <cstdio>
#include <cstring>
#include <algorithm>

int N;
int grape[10001];
int dp[10001][3];

// state는 상황 저장.

// 이전에 연속으로 몇개를 먹었는지를 저장한다.
int juice(int curr, int state) {
	if (curr == N) return 0;
	int& ret = dp[curr][state];
	if (ret != -1) return ret;

	// 실제 계산

	// 1. 안 먹고 다음으로 넘겨
	ret = juice(curr + 1, 0);

	// 2. 만약 state가 2가 아니라면
	if (state != 2) {
		ret = std::max(ret, juice(curr + 1, state + 1) + grape[curr]);
	}

	return ret;
}

int main() {
	scanf("%d", &N);

	memset(dp, -1, sizeof(dp));

	for (int i = 0; i < N; i++) {
		scanf("%d", grape + i);
	}
	
	printf("%d", juice(0, 0));
}