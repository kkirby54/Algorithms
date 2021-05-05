#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

int N, dp[100001];
int arr[325];

int sq_nums(int curr) {
	if (curr == 0) return 0;

	int& ret = dp[curr];
	if (ret != -1) return ret;

	ret = 987654321;
	for (int i = (int)sqrt(curr); i >= 1; i--) {
		ret = std::min(ret, sq_nums(curr - arr[i]) + 1);
	}

	return ret;
}

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= 320; i++) {
		arr[i] = i * i;
		//printf("%d\n", arr[i]);
	}

	memset(dp, -1, sizeof(dp));

	printf("%d", sq_nums(N));

}