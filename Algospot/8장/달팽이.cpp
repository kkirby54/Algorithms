#include <cstdio>
#include <cstring>
#include <algorithm>

int C, N, M;
double dp[1001][1001];

double snail(int curr, int days) {
	// 이 경우에는 안됨.
	// curr이 N보다 작아야,
	// 즉 못 올라가야됨.
	if (curr >= N) return 0;
	if (days >= M) return 1;

	double& ret = dp[curr][days];
	if (ret != -1) return ret;

	ret = 0;
	// 0.75 확률
	ret += (snail(curr + 2, days + 1) * 0.75);
	
	// 0.25 확률
	ret += (snail(curr + 1, days + 1) * 0.25);

	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				dp[i][j] = -1;
		}

		printf("%.10lf\n",1- snail(0, 0));

	}


}