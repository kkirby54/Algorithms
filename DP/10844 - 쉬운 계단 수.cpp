#include <cstdio>
#include <algorithm>

const int MOD = 1000000000;

int N;
int dp[101][10];

int stair(int curr, int state) {
	if (curr == 1) return 1;

	int& ret = dp[curr][state];
	if (ret) return ret;

	ret = 0;
	if (state != 0) {
		ret += (stair(curr - 1, state - 1) % MOD);
	}
	if (state != 9) {
		ret += (stair(curr - 1, state + 1) % MOD);
	}

	return (ret % MOD);
}

int main() {
	scanf("%d", &N);

	int sum = 0;

	for (int i = 1; i <= 9; i++) {
		sum += (stair(N, i) % MOD);
		sum %= MOD;
	}
	printf("%d", sum);
}

