#include <cstdio>
#include <cstring>
#include <algorithm>

int C, N, arr[101][101], dp[101][101], dp2[101][101];

int triangle(int r, int c) {
	// 마지막 행에 도달하면 리턴
	if (r == N - 1) return arr[r][c];

	int& ret = dp[r][c];
	if (ret != -1) return ret;

	ret = triangle(r + 1, c) + arr[r][c];
	ret = std::max(ret, triangle(r + 1, c + 1) + arr[r][c]);

	return ret;
}

int cntCheck(int r, int c) {
	if (r == N-1) {
		return 1;
	}

	int& ret = dp2[r][c];
	if (ret != -1) return ret;

	ret = 0;
	if (triangle(r, c) == triangle(r + 1, c) + arr[r][c]) {
		ret += cntCheck(r + 1, c);
	}
	if (triangle(r, c) == triangle(r + 1, c + 1) + arr[r][c])
		ret += cntCheck(r + 1, c + 1);

	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);
		memset(dp, -1, sizeof(dp));
		memset(dp2, -1, sizeof(dp));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				scanf("%d", &arr[i][j]);
			}
		}

		printf("%d\n", cntCheck(0, 0));
	}

}