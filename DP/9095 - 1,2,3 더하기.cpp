#include <cstdio>

int dp[13];

int func(int curr) {
	if (curr <= 2) return curr;
	if (curr == 3) return 4;

	int& ret = dp[curr];
	if (ret) return ret;

	return ret = func(curr - 1) + func(curr - 2) + func(curr - 3);

}

int main() {
	int T, num;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%d", &num);

		printf("%d\n", func(num));
	}

}