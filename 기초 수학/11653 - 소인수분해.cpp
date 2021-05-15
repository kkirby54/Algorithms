#include <cstdio>
#include <algorithm>
#include <vector>

const int MAX = 10000001;
int N, tmp, k;
bool isPrime[MAX];
std::vector<int> Prime;

int main() {
	// N을 분해
	scanf("%d",&N);

	// Eratos로 찾기
	std::fill(isPrime, isPrime + N+1, true);
	isPrime[1] = false;
	for (int i = 4; i <= MAX; i += 2)
		isPrime[i] = false;
	
	Prime.push_back(2);
	for (int i = 3; i < MAX; i += 2) {
		if (!isPrime[i]) continue;

		Prime.push_back(i);
		if (i > 3162) continue;
		for (int j = i * i; j < MAX; j += 2 * i) {
			isPrime[j] = false;
		}
	}

	k = 0;
	while (N != 1) {
		if ((N % Prime[k]) != 0) k++;
		else {
			printf("%d\n", Prime[k]);
			N /= Prime[k];
		}
	}
}