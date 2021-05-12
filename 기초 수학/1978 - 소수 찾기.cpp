#include <cstdio>
#include <algorithm>
#include <vector>

const int MAX = 1001;

int main() {
	int N, tmp;
	bool isPrime[MAX];
	scanf("%d", &N);

	// Eratos로 찾기
	std::fill(isPrime, isPrime + MAX, true);
	isPrime[1] = false;
	for (int i = 4; i < MAX; i += 2)
		isPrime[i] = false;
	
	for (int i = 3; i < MAX; i += 2) {
		if (!isPrime[i]) continue;
		for (int j = i * i; j < MAX; j += i)
			isPrime[j] = false;
	}

	int cnt = 0;

	for (int i = 0; i < N; i++) {
		scanf("%d", &tmp);
		if (isPrime[tmp]) cnt++;
	}
	printf("%d", cnt);
}