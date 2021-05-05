#include <cstdio>
#include <algorithm>
#include <cstring>

int N, cost[1001];
int dp[1001][1001];

// K는 앞으로 사야할 개수
int card(int curr, int k) {
	if (k == 0) return 0;
	if (curr == N) return 0;

	int& ret = dp[curr][k];
	if (ret != -1) return ret;

	// 안 사고 넘김
	ret = card(curr + 1, k);

	// 하나 삼
	if (k - (curr + 1) >= 0)
		ret = std::max(ret, card(curr, k - (curr+1)) + cost[curr]);
	
	// 사고 넘김
	if (k - (curr + 1) >= 0)
		ret = std::max(ret, card(curr + 1, k - (curr+1)) + cost[curr]);

	return ret;
}

int main() {
	scanf("%d", &N);
	memset(dp, -1, sizeof(dp));


	for (int i = 0; i < N; i++) {
		scanf("%d", cost + i);
	}

	printf("%d", card(0, N));

}