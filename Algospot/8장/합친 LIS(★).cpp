#include <cstdio>
#include <algorithm>

const long long INF = std::numeric_limits<long long>::min();

int A[101], B[101], C, N, M;
int ans = -87654321;
int dp[101][101];

int JLIS(int idxA, int idxB) {
	int& ret = dp[idxA+1][idxB+1];
	if (ret != -1) return ret;

	ret = 2;

	// 1 2 4
	// 3 4 7

	long long a = idxA == -1 ? INF : A[idxA];
	long long b = idxB == -1 ? INF : B[idxB];

	long long MaxElement = std::max(a, b);

	for (int nextA = idxA + 1; nextA < N; nextA++) {
		if (MaxElement < A[nextA]) {
			ret = std::max(ret, JLIS(nextA, idxB) +1);
		}
	}

	for (int nextB = idxB + 1; nextB < M; nextB++) {
		if (MaxElement < B[nextB]) {
			ret = std::max(ret, JLIS(idxA, nextB) + 1);
		}
	}

	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%d", A + i);
		for (int i = 0; i < M; i++)
			scanf("%d", B + i);

		memset(dp, -1, sizeof(dp));

		printf("%d\n", JLIS(-1, -1) - 2);

	}

}