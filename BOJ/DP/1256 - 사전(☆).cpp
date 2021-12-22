#include <cstdio>
#include <algorithm>
#include <cstring>
const int INF = 1000000000;
int N, M, K;

int dp[202][101][101];

int dictionary(int pos, int n, int m) {
	if (pos == 0) return 1;
	if (n == 0 || m == 0) return 1; // 0이 되면 그 순간 다 정해짐.
	
	int& ret =  dp[pos][n][m];
	if (ret != -1) return ret;

	return ret = std::min(INF, dictionary(pos - 1, n - 1, m) +
		dictionary(pos - 1, n, m - 1));
}

char ret[205];
void findK(int pos, int n, int m, int k, int p) {
	if (pos == 0) return;
	if (n == 0) {
		// 나머지는 다 m, 즉 'z'로 채우기
		for (int i = 0; p + i < N + M; i++) {
			ret[p + i] = 'z';
		}
		return;
	}
	if (m == 0) {
		for (int i = 0; p + i < N + M; i++) {
			ret[p + i] = 'a';
		}
		return;
	}

	int pivot = dictionary(pos-1, n-1, m);
	if (pivot > k) {
		ret[p] = 'a';
		findK(pos - 1, n - 1, m, k, p+1);
	}
	else {
		ret[p] = 'z';
		findK(pos - 1, n, m - 1, k - pivot, p + 1);
	}

}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	memset(dp, -1, sizeof(dp));

	//printf("%d\n", dictionary(N + M, N, M));
	if (dictionary(N + M, N, M) < K) {
		printf("-1");
		return 0;
	}

	findK(N + M, N, M, K-1, 0);
	printf("%s", ret);
}