#include <cstdio>
#include <algorithm>
const int MOD = 1000000000;

int N;
int dp[101][10][1024];

int solve(int curr, int last, int status) {
	if (curr == N) {
		// status가 다 켜져있으면 가능
		if (status == (1 <<10) -1) {
			return 1;
		}
		return 0;
	}

	int& ret = dp[curr][last][status];
	if (ret != -1) return ret;
	
	ret = 0;

	if (last != 0) {
		ret += solve(curr + 1, last - 1, status | (1 << last-1));
		ret %= MOD;
	}
	
	if (last != 9) {
		ret += solve(curr + 1, last + 1, status | (1 << last +1));
		ret %= MOD;
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));

	int ret = 0;
	for (int i = 1; i < 10; i++) {
		ret += solve(1, i, 1 << i);
		ret %= MOD;
	}

	printf("%d\n", ret);
}