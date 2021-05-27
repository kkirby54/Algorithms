#include <cstdio>
#include <cstring>
#include <algorithm>

int N;
int arr[1001];

// DP 배열의 의미
// 그 때까지의 가장 긴 거리를 저장한다.
int dp[1001];

int main() {
	scanf("%d", &N);

	int Mx = 0;

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
		Mx = std::max(Mx, dp[i]);
	}

	printf("%d", Mx);
}