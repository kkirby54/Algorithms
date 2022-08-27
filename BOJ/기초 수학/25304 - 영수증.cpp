#include <cstdio>

int main() {
	int X, N;
	int price, nums;

	long long ret = 0;

	scanf("%d %d", &X, &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &price, &nums);

		ret += (1LL * price * nums);
	}

	printf("%s", ret == X ? "Yes" : "No");

}