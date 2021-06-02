#include <cstdio>
#include <cstring>
#include <algorithm>

int C, N, D, P, T, Q;
int A[51][51];
int edge_nums[51];
double dp[51][101];

// days일 후에 curr에 숨어있을 확률
// 반대로 푼다. Q부터 시작해서 P로 돌아온다고 하자.
double dunibal(int curr, int days) {
	if (days == 0) return curr == P ? 1 : 0;

	double& ret = dp[curr][days];
	if (ret != -1) return ret;

	ret = 0;
	// curr에 인접한 애들을 찾는다.
	for (int next = 0; next < N; next++) {
		// 인접한 애들에 대해서.
		if (A[curr][next]) {
			// days-1 만에 next에 도착한다.
			ret += ((dunibal(next, days - 1) * (1 / (double) edge_nums[next])));
		}
	}

	return ret;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d %d", &N, &D, &P);

		std::fill(edge_nums, edge_nums + N, 0);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &A[i][j]);
				if (A[i][j] == 1) edge_nums[i]++;
			}
		}

		scanf("%d", &T);
		for (int i = 0; i < T; i++) {
			scanf("%d", &Q);

			for (int i = 0; i < 51; i++) {
				for (int j = 0; j < 100; j++)
					dp[i][j] = -1;
			}

			// D일 후 Q에 숨어있을 확률을 구해야 한다.
			printf("%.8lf ", dunibal(Q, D));
		}
		puts("");
	}
}