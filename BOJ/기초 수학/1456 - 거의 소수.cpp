#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;
const int MAX_V = 10000000;

long long A, B;
int isPrime[MAX_V + 1]; // 제일 작은 소인수를 저장한다.

void eratos() {
	// 전처리
	// hi까지의 소수를 이미 구해둔다.
	// 가장 작은 소인수를 미리 저장해둔다.
	for (int i = 2; i <= MAX_V; i++) isPrime[i] = i;
	isPrime[0] = isPrime[1] = -1;

	int sqrV = int(sqrt(MAX_V));

	// 일단 짝수 버리기.
	for (int i = 4; i <= MAX_V; i += 2) {
		isPrime[i] = 2;
	}

	for (int i = 3; i <= sqrV; i++) {
		// 소수일 때만 시행
		if (isPrime[i] != i) continue;

		for (int j = i * i; j <= MAX_V; j += i * 2)
			if (isPrime[j] == j)
				isPrime[j] = i;
	}
}

int main() {
	eratos();

	scanf("%lld %lld", &A, &B);
	vector<long long> ret;

	// 소수의 N제곱 꼴을 다 저장한다.
	for (int i = 0; i <= 10000000; i++) {
		// 소수라면
		if (isPrime[i] == i) {
			// 걔네들의 k제곱꼴을 vec에 넣는다.
			int k = 2;
			
			// i의 K제곱이 일단 1e14를 넘으면 안돼.
			while (pow(i, k) <= 1e14) {
				ret.push_back(long long(pow(i, k)));
				k++;
			}
		}
	}
	sort(ret.begin(), ret.end());

	auto itr1 = upper_bound(ret.begin(), ret.end(), B) - ret.begin();
	auto itr2 = lower_bound(ret.begin(), ret.end(), A) - ret.begin();

	long long result = (long long) itr1 - itr2;
	printf("%lld\n", result);

}