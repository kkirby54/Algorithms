#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
const long long MAX = 1001000;

long long A, B;
bool isPrime[MAX+1];
bool MinBasedSqrPrime[MAX + 1];

void getPrime() {
	fill(isPrime, isPrime + MAX + 1, true);
	isPrime[0] = isPrime[1] = false;

	for (int i = 2; i <= MAX; i++) {
		if (!isPrime[i]) continue;

		for (long long j = (long long)i * i; j <= MAX; j += i)
			isPrime[j] = false;
	}

}

int main() {
	getPrime();
	fill(MinBasedSqrPrime, MinBasedSqrPrime + MAX + 1, 1);
	scanf("%lld %lld", &A, &B);

	// 이제 [A, B] 이걸 구한다.
	long long ret = 0;

	// 소수들만 본다
	for (int i = 0; i < MAX; i++) {
		if (!isPrime[i]) continue;

		// 소수들의 제곱을 지워 나간다.
		long long curr = (long long) i * i;

		// A부터 B까지의 범위 중에서, curr의 배수를 지우면 된다.
		// A <= curr * X 인 정수 X를 찾는다.
		long long j = ((A-1) / curr) + 1;

		while (curr*j <= B) {
			// curr * j를 지워나간다.
			// curr * j가 매우 큰 수가 때문에 A를 빼서
			// 인덱스를 맞춰줘야한다.
			// 이게 가능한 이유는 B - A의 범위가 1백만이기 때문이다.
			if (MinBasedSqrPrime[curr * j - A]) {
				MinBasedSqrPrime[curr * j - A] = false;
				ret++;
			}
			j++;
		}
	}
	printf("%lld\n", (B - A + 1) - ret);

}