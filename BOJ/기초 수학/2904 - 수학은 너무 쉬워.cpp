#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;
const int MAX_V = 1000000;

int N;
int isPrime[MAX_V + 1]; // 제일 작은 소인수를 저장한다.
int PrimePower[MAX_V + 1]; // 소수가 총 몇번 나왔는지를 센다.
int tempPrimePower[MAX_V + 1];

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

	int N, arr[100];
	int GCD = 1;
	vector<int> ConsistPrime;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
		int temp = arr[i];

		while (temp > 1) {
			PrimePower[isPrime[temp]]++;
			temp /= isPrime[temp];
		}
	}

	for (int i = 0; i <= MAX_V; i++) {
		if (isPrime[i] != i) continue;
		PrimePower[i] /= N;
		if (PrimePower[i] != 0) {
			GCD *= (int)pow(i, PrimePower[i]);
			ConsistPrime.push_back(i);
		}
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		// arr[i]를 소인수 분해해서 저장한다.
		int temp = arr[i];
		memset(tempPrimePower, 0, sizeof(tempPrimePower));

		while (temp > 1) {
			tempPrimePower[isPrime[temp]]++;
			// 젤 작은 소인수로 나눠본다.
			temp /= isPrime[temp];
		}

		// 이제 비교한다.
		// 최대공약수와 이를 구성하는 소인수를 PrimePower와
		// ConsistPrime으로 저장해뒀음.
		for (int j = 0; j < ConsistPrime.size(); j++) {
			int currPrime = ConsistPrime[j];
			if (PrimePower[currPrime] - tempPrimePower[currPrime] > 0) {
				ret += PrimePower[currPrime] - tempPrimePower[currPrime];
			}
		}
	}

	printf("%d %d\n", GCD, ret);


}