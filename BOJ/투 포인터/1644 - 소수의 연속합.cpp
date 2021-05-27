#include <cstdio>
#include <algorithm>
#include <vector>

const int MAX = 4000000;

int N;
bool isPrime[MAX];
std::vector<int> Prime(1, 2);

int main() {
	scanf("%d", &N);
	std::fill(isPrime, isPrime + N+1, true);

	// 2를 제외한 짝수를 다 false
	for (int i = 4; i <= N; i+= 2) {
		isPrime[i] = false;
	}

	// 3부터 보면서 소수 판별
	for (int i = 3; i <= N; i += 2) {
		if (!isPrime[i]) continue;
		Prime.push_back(i);
		for (int j = i * 2; j <= N; j += i)
			isPrime[j] = false;
	}

	int s = 0, e = 0, ret = 0;
	long long sum = 0;
	int prime_nums = Prime.size();

	//for (int e : Prime) {
	//	printf("%d, ", e);
	//}

	while (1) {
		if (sum >= N) sum -= Prime[s++];
		else if (e == prime_nums) break;
		else sum += Prime[e++];

		if (sum == N) ret++;

	}

	printf("%d", ret);

}