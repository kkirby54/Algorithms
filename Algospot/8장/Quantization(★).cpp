#include <cstdio>
#include <algorithm>
#include <cstring>

const int INF = 987654321;

int C, N, arr[101], S;
int dp[101][11];


// [a,b]까지.. 오차 제곱의 합 return
// 2021. 05. 30 : 멍청하게 돌렸는데, 다음에는 부분합으로 풀기.
int MinErr(int a, int b) {
	int len = b - a + 1;

	int sum = 0;
	for (int i = a; i <= b; i++) {
		sum += arr[i];
	}

	int average = sum / len;
	// average나 average + 1로 계산한다.
	// average -1로 계산
	int s1 = 0, s2 = 0, s3 = 0;

	for (int i = a; i <= b; i++) {
		s1 += (average - arr[i]) * (average - arr[i]);
		s2 += (average + 1 - arr[i]) * (average + 1 - arr[i]);
		s3 += (average - 1 - arr[i]) * (average - 1 - arr[i]);
	}

	return std::min(s3, std::min(s1, s2));
}

int Quantize(int from, int part) {
	if (from >= N) return 0;
	if (part == 1) return MinErr(from, N - 1);
	if (part == 0) return INF;

	int& ret = dp[from][part];
	if (ret != -1) return ret;

	ret = INF;

	// from + size의 의미
	// 우리는 [from, from+size-1]을 처리한다.
	// 따라서, 다음에 처리하는 거는 [from + size, ~] 인데
	// 한 번에 arr 배열을 모두 훑을 수도 있으므로 from + size == N이 될 때까지로 생각한다.
	for (int size = 1; from + size <= N; size++) {

		// 현재는 size만큼의 수열로 넘긴다.
		// 따라서 [from, from + size - 1]은
		// MinErr() 함수로 오차 제곱의 합을 구한다.

		// 나머지는 재귀로 넘긴다.
		ret = std::min(ret, Quantize(from + size, part - 1) +
			MinErr(from, from + size - 1));

	}

	return ret;
}



int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &S);
		
		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);
		}

		std::sort(arr, arr + N);

		memset(dp, -1, sizeof(dp));

		printf("%d\n", Quantize(0, S));

	}

}