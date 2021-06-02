#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
int dp[101];
int tile(int curr) {
	if (curr <= 2) return curr;

	int& ret = dp[curr];
	if (ret != -1) return ret;

	return ret = (tile(curr - 1) + tile(curr - 2)) % MOD;
}

int asymtile(int curr) {
	int ret = tile(curr);
	if (curr % 2 == 0) {
		ret = (ret - tile(curr / 2) + MOD) % MOD;
		ret = (ret - tile((curr - 2) / 2) + MOD) % MOD;
	}
	else {
		return (ret - tile((curr - 1) / 2) + MOD) % MOD;
	}

	return ret;
}


int C, N;

int main() {
	scanf("%d", &C);
	memset(dp, -1, sizeof(dp));

	int ans;

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		if (N <= 2) ans = 0;
		else if (N <= 4) ans = 2;
		else ans = asymtile(N);

		printf("%d\n", ans);
	}

}