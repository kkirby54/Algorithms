#include <cstdio>
#include <algorithm>
#include <cstring>

int T;
int N, M, A[3000], B[100];
int dp[3002][102][102][2];

int spotmart(int n, int mBest, int mWorst, bool prev) {
	int& ret = dp[n][mBest][mWorst][prev];
	if (ret != -1) return ret;

	// Base Case.
	// lots of trying: n == N이면 그냥 return 0했는데,
	// 이러면 A는 전부 훑었지만 B는 훑지 못한다.
	// 따라서 A와 B가 전부 끝날 시에 Base case를 작성해야 한다.
	if (n == N && mBest + mWorst == M) return ret = 0;
	// if (mBest + mWorst > M) return ret = 0;

	ret = 0;
	if (n < N)
		ret = spotmart(n + 1, mBest, mWorst, 0);
	if (mBest + mWorst < M)
		ret = std::max(ret, spotmart(n, mBest, mWorst + 1, 0));

	// 이전에 사용하지 않았다면, 이번에 사용해도 된다.
	if (!prev) {
		if (n < N)
			ret = std::max(ret, spotmart(n + 1, mBest, mWorst, 1) + A[n]);
		if (mBest + mWorst < M)
			ret = std::max(ret, spotmart(n, mBest + 1, mWorst, 1) + B[M - 1 - mBest]);
	}

	return ret;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", A + i);

		scanf("%d", &M);
		for (int i = 0; i < M; i++)
			scanf("%d", B + i);

		std::sort(B, B + M);
		memset(dp, -1, sizeof(dp));


		int ret = spotmart(0, 0, 0, 0);

		printf("#%d %d\n",t, ret);


	}

}