#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;
int C, N, K;

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &K, &N);
		queue<long long> Q;
		long long sum = 0;
		int ret = 0;
		long long signal;
		long long num = 1983;

		while (N--) {
			signal = (num % 10000) + 1;
			Q.push(signal);
			sum += signal;

			if (sum == K) ret++;
			while (sum >= K && !Q.empty()) {
				// 앞에서부터 뺀다.
				sum -= Q.front();
				if (sum == K) ret++;
				Q.pop();
			}


			num = ((num * 214013 + 2531011) % (long long)(pow(2, 32)));
		}


		printf("%d\n", ret);
	}

}
