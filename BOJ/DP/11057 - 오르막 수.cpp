#include <cstdio>
#include <algorithm>

const int MOD = 10007;

int N;
int dp[1001][10];

int stair(int curr, int state) {
	if (curr == 1) return 1;

	int& ret = dp[curr][state];
	if (ret) return ret;

	ret = 0;
	for (int i = 0; state + i < 10; i++)
		ret += (stair(curr - 1, state + i) % MOD);


	return (ret % MOD);
}

int main() {
	scanf("%d", &N);

	int sum = 0;

	for (int i = 0; i <= 9; i++) {
		sum += (stair(N, i) % MOD);
		sum %= MOD;
	}
	printf("%d", sum);
}

