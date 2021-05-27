#include <cstdio>


int GCD(int a, int b) {
	while (1) {
		int r = a % b;
		if (!r) break;

		a = b;
		b = r;
	}

	return b;
}

int main() {
	int T, N;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		int arr[101];
		long long ret = 0;

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);

			for (int j = 0; j < i; j++) {
				ret += GCD(arr[i], arr[j]);
			}
		}
		printf("%lld\n", ret);
	}

}