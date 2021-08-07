#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

const int INF = 987654321;
using namespace std;

int C, N, S;
int arr[105];
int dp[105][15];
int pSum[105], ppSum[105];

// arrr을 양자화한다. S개의 수로.
// 오차 제곱의 합을 최소로 만들어야 한다.

// [a,b]를 양자화한다.
int quantize(int a, int b) {
	if (a > b) return INF;

	// pSum[b+1] - pSum[a].
	int total_pSum = pSum[b + 1] - pSum[a];
	int average = int(0.5 + (double)total_pSum / (b - a + 1));

	// average -> 0.5를 더해서 올라가면 그 처리
	/*double temp = ((total_pSum) / (double)(b - a + 1));
	int average;
	if (int(temp + 0.5) == (int(temp) + 1)) average = int(temp) + 1;
	else average = int(temp);*/

	int total_ppSum = ppSum[b + 1] - ppSum[a];

	return (total_ppSum - 2 * total_pSum * average + average * average * (b - a + 1));
}

// curr부터 시작, rest개의 묶음으로 나눠야 한다.
// 그 중 최소의 오류
int divide(int curr, int rest) {
	if (curr == N) return 0;
	if (rest == 1) return quantize(curr, N - 1);
	if (rest == 0) return INF;

	int& ret = dp[curr][rest];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = curr; i < N; i++) {
		// [curr, i]까지 나눈다는 의미. 그리고 묶음으로 하나 쓴다.
		// [curr, i]까지 양자화하고, 나머지는 재귀로 넘긴다.
		int QuantizationValue = quantize(curr, i);

		ret = min(ret, QuantizationValue + divide(i + 1, rest - 1));
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
		sort(arr, arr + N);
		for (int i = 0; i < N; i++) {
			pSum[i + 1] = pSum[i] + arr[i];
			ppSum[i + 1] = ppSum[i] + arr[i] * arr[i];
		}

		memset(dp, -1, sizeof(dp));

		printf("%d\n", divide(0, S));
	}

}