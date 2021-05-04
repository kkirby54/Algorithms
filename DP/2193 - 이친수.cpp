#include <cstdio>
#include <algorithm>

int N;
long long dp[91];

long long pinary(int curr) {
	if (curr == 1 || curr == 2) return 1;

	long long& ret = dp[curr];
	if (ret) return ret;

	return ret = pinary(curr - 1) + pinary(curr - 2);
}

int main() {
	scanf("%d", &N);

	printf("%lld", pinary(N));

}