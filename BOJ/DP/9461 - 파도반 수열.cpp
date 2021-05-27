#include <cstdio>
#include <algorithm>

int T, N;
long long dp[101];

long long padovan(int curr) {
	if (curr <= 3) return 1;
	long long& ret = dp[curr];
	if (ret) return ret;

	return ret = padovan(curr - 2) + padovan(curr - 3);

}

int main() {
	scanf("%d", &T);
	
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);

		printf("%lld\n", padovan(N));

	}


}