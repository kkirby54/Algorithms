#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

const int MAX_N = 10000000;

// 에라토스테네스의 체.
int N, C, lo, hi;
int minFactor[MAX_N + 1];
int dp[MAX_N + 1];

void eratos2() {
	minFactor[0] = minFactor[1] = -1;

	for (int i = 2; i <= MAX_N; i++)
		minFactor[i] = i;

	int sqrtn = (int)sqrt(MAX_N);
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= MAX_N; j += i) {
				if (minFactor[j] == j)
					minFactor[j] = i;
			}
		}
	}
}

// n을 소인수분해한다.
// 그리고 약수의 개수를 return?
int measureCnt(int n) {
	int& ans = dp[n];
	if (ans) return ans;

	std::vector<int> ret;

	while (n != 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}

	int curr = 0;
	int len = 0;
	int arr[100] = { 0 };
	for (int i = 0; i < ret.size(); i++) {
		// 초기화해버리고 cnt도 1로 만들어
		if (curr != ret[i]) {
			curr = ret[i];
			len++;
			(arr[len])++;
		}
		else (arr[len])++;

	}

	ans = 1;
	for (int i = 1; i <= len; i++) {
		ans *= (arr[i] + 1);
	}

	return ans;
}

int main() {
	scanf("%d", &C);
	eratos2();

	for (int t = 0; t < C; t++) {
		scanf("%d %d %d", &N, &lo, &hi);
		int cnt = 0;

		for (int i = lo; i <= hi; i++) {
			if (measureCnt(i) == N) {
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}

}