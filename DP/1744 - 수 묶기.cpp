#include <cstdio>
#include <cstring>
#include <algorithm>

const int MIN = -2000000000;

int N, arr[10000];
int dp[10000];

int bind(int curr) {
	if (curr == N) return 0;
	if (curr == N - 1) return arr[curr];

	int& ret = dp[curr];
	if (ret != MIN) return ret;

	// curr 더하고 넘어가냐
	ret = arr[curr] + bind(curr + 1);

	// arr[curr] * arr[curr+1]
	ret = std::max(ret, bind(curr + 2) + arr[curr] * arr[curr + 1]);

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N);

	std::fill(dp, dp + N, MIN);

	printf("%d", bind(0));

}