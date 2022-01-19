#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>
const int MOD = 1000000007;

int T;
int len, ret;
char str[10001];
// 그니까 넘어갈 때, 최소한 하나는 겹치는 게 있어야 한다.

int dp[10001][16];

int solve2(int curr, int val) {
	if (curr == len) return 1;

	int& ret = dp[curr][val];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 1; i < 16; i++) {
		// 1. curr번째를 반드시 포함해야 하며,
		// 2. 지난 val과 공통된 부분이 있어야 한다.
		if ((i & (1 << str[curr] - 'A')) && (val & i)) {
			ret += solve2(curr + 1, i) % MOD;
			ret %= MOD;
		}
	}

	return ret;
}

int main() {
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%s", str);

		// str[i] - 'A'로 접근가능.
		len = strlen(str);
		memset(dp, -1, sizeof(dp));

		int sum = 0;
		for (int i = 1; i < 16; i++) {
			if (i & (1 << str[0] - 'A') && (i & (1 << 0))) {
				sum += solve2(1, i);
				sum %= MOD;
			}
		}


		printf("#%d %d\n", t + 1, sum);
	}

}