#include <cstdio>
#include <algorithm>

int N;
int arr[100000];
int dp[100000];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	int Mx = -987654321;

	for (int i = 0; i < N; i++) {
		dp[i] = arr[i];

		if (i != 0 && dp[i - 1] + dp[i] >= dp[i]) {
			dp[i] += dp[i-1];
		}

		Mx = std::max(Mx, dp[i]);
	}

	printf("%d", Mx);

}