#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 987654321;

int C, len;
char numbers[10001];
int dp[10001];

// curr부터 cnt개를 쓸 때 점수를 리턴한다.
int getState(int curr, int cnt) {
	// 범위 초과 시 INF
	if (curr + cnt + 1 == len) return INF;

	// 1. 모든 숫자 같을 때 난이도 1
	bool state = 1;
	for (int i = curr; i < curr + cnt; i++) {
		if (numbers[i] != numbers[curr]) state = 0;
	}
	if (state) return 1;

	// 2. 등차수열 이룰 때
	state = 1;
	bool arithmetic = true;
	int d = numbers[curr + 1] - numbers[curr];
	for (int i = curr + 1; i < curr + cnt; i++) {
		if (d != (numbers[i] - numbers[i - 1])) {
			state = 0;
			arithmetic = false;
		}
	}
	if (state) {
		// d가 -1 또는 1이면 단조 감소/증가, 점수는 2
		if (d == -1 || d == 1) return 2;
		// 아직 난이도 5는 냅둔다.
	}

	state = 1;
	for (int i = curr; i < curr + cnt; i++) {
		// numbers[i]와 number[i+2]가 같나?
		if (i + 2 < curr + cnt)
			if (numbers[i] != numbers[i + 2])
				state = 0;
	}
	if (state) return 4;

	if (arithmetic) return 5;
	return 10;
}

int PI(int curr) {
	if (curr >= len) return 0;

	int& ret = dp[curr];
	if (ret != -1) return ret;	

	// 3개
	ret = INF;
	for (int i = 3; i <= 5; i++) {
		ret = std::min(ret, PI(curr + i) + getState(curr, i));
	}
	
	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%s", numbers);
		memset(dp, -1, sizeof(dp));
		len = strlen(numbers);

		printf("%d\n", PI(0));
	}

}
