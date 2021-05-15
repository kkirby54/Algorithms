#include <cstdio>

const int MAX = 1000001;
bool NotPrime[MAX];

int main() {
	int N;

	for (int i = 4; i < MAX; i += 2) {
		NotPrime[i] = true;
	}

	for (int i = 3; i <= 1000; i += 2) {
		if (NotPrime[i]) continue;
		
		for (int j = i * i; j < MAX; j += 2 * i)
			NotPrime[j] = true;
	}

	while (1)
	{
		scanf("%d", &N);
		if (!N) return 0;

		for (int i = 2; i <= N; i++) {
			if (!NotPrime[i] && !NotPrime[N - i]) {
				printf("%d = %d + %d\n", N, i, N - i);
				break;
			}
		}

	}

}