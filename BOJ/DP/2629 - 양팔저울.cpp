#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int weight[30];
int M, ballWeight;
bool isPossible;

int dp[31][80001];

void armScale(int curr, int remain) {
	if (remain == 40000) {
		isPossible = true; return;
	}
	if (curr == N) return;

	int& ret = dp[curr][remain];
	if (ret != -1) return;

	ret = 1;
	// 안 쓰는 경우
	armScale(curr + 1, remain);

	// 빼는 경우.
	armScale(curr + 1, remain - weight[curr]);

	// 더하는 경우
	armScale(curr + 1, remain + weight[curr]);


	return;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", weight + i);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		isPossible = false;
		scanf("%d", &ballWeight);
		
		memset(dp, -1, sizeof(dp));
		armScale(0, 40000 + ballWeight);

		if (isPossible) printf("Y ");
		else printf("N ");
	}
}