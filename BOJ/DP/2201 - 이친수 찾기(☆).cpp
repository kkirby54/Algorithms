#include <cstdio>
#include <cstring>

long long K;
long long dp[101][2];

long long pinary(int n, bool curr) {
	long long& ret = dp[n][curr];
	if (ret != -1) return ret;
	if (n == 1) return 1;

	ret = pinary(n - 1, 0);
	if (curr == 0)
		ret += pinary(n - 1, 1);

	return ret;
}

int ret[101];
void skip(int n, bool curr, long long k, int p) {
	if (n == 0) return;

	long long pivot = pinary(n - 1, 0);
	if (pivot > k) {
		ret[p] = 0;
		skip(n - 1, 0, k, p + 1);
	}
	else {
		ret[p] = 1;
		skip(n - 1, 1, k - pivot, p + 1);
	}
}

int main() {
	scanf("%lld", &K);
	memset(dp, -1, sizeof(dp));
	long long sum = 0;
	int digit = 0;
	for (int i = 1; ; i++) {
		if (sum + pinary(i, true) >= K) {
			// i번째까지 해서 했는데 K가 포함된다면,
			// K번째 수는 i자리인 것임.
			digit = i;
			break;
		}
		sum += pinary(i, true);
	}

	ret[0] = 1;
	skip(digit, 1, K - sum - 1, 1);
	for (int i = 0; i < digit; i++) {
		printf("%d", ret[i]);
	}



}