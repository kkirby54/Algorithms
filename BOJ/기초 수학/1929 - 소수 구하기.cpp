#include <cstdio>
#include <algorithm>

const int MAX = 1000001;
int M, N, tmp;
bool isPrime[MAX];

int main() {
	scanf("%d %d", &M, &N);

	// Eratos로 찾기
	std::fill(isPrime, isPrime + MAX, true);
	isPrime[1] = false;
	for (int i = 4; i < MAX; i += 2)
		isPrime[i] = false;
	
	for (int i = 3; i < 1000; i += 2) {
		if (!isPrime[i]) continue;
		for (int j = i * i; j < MAX; j += 2 *i)
			isPrime[j] = false;
	}

	for (int i = M; i <= N; i++) {
		if (isPrime[i]) printf("%d\n", i);
	}

}