#include <cstdio>
#include <cstring>
#include <algorithm>

int N;
int arr[1001];

int dp[1001];

// 항상 커야함.

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	int Mx = 0;

	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arr[i] < arr[j]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
		Mx = std::max(Mx, dp[i]);
	}

	printf("%d", Mx);
}