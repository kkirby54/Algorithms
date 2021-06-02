#include <cstdio>
#include <cstring>

const int MOD = 10000000;

int C, N, dp[101][101];

int poly(int prev, int rest) {
	if (rest == 0) return 1;

	int& ret = dp[prev][rest];
	if (ret != -1) return ret;

	int tmp;
	ret = 0;

	// 최대 rest만큼 써야 한다.
	for (int i = 1; i <= rest; i++) {
		// 실제로 i개 만큼을 써본다.
		// prev에 따라 다른데,
		// prev == 0이라면 처음. 그래서 무조건 1개
		// 아니라면 i + prev - 1개를 쓴다.
		if (prev == 0) tmp = 1;
		else
			tmp = (i + prev - 1) % MOD;

		// 그니까.. i개를 쓰는데,
		// i + prev - 1개의 후보지가 있다는 말이다.
		// 그러면 넘기는
		// poly(i, rest - i)라는 애가
		// i + prev - 1개가 있다는 말이잖아.

		ret += (tmp * (poly(i, rest - i) % MOD)) % MOD;
		
		// 이 처리 안해서 답이 안나옴.
		ret %= MOD;
	}
	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		memset(dp, -1, sizeof(dp));

		printf("%d\n", poly(0, N));

	}

}