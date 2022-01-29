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
	// lots of trying: n == N�̸� �׳� return 0�ߴµ�,
	// �̷��� A�� ���� �Ⱦ����� B�� ���� ���Ѵ�.
	// ���� A�� B�� ���� ���� �ÿ� Base case�� �ۼ��ؾ� �Ѵ�.
	if (n == N && mBest + mWorst == M) return ret = 0;
	// if (mBest + mWorst > M) return ret = 0;

	ret = 0;
	if (n < N)
		ret = spotmart(n + 1, mBest, mWorst, 0);
	if (mBest + mWorst < M)
		ret = std::max(ret, spotmart(n, mBest, mWorst + 1, 0));

	// ������ ������� �ʾҴٸ�, �̹��� ����ص� �ȴ�.
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