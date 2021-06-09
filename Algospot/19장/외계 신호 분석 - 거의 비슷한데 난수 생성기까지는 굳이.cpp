#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}

	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}

};

int C, N, K;

int main() {
	scanf("%d", &C);

	for (int i = 0; i < C; i++) {
		scanf("%d %d", &K, &N);

		RNG rng;
		std::queue<int> Q;

		int sum = 0, cnt = 0, newSignal;

		// 큐에 일단 넣고 본다.
		// 넣은 다음에
		// sum의 크기에 따라 다르다.
		// 1. sum == K. cnt++, 그리고 큐에 있는거 하나 빼기
		// 2. sum < K. 이러면 그냥 continue;
		// 3. sum > K. 그럼 큐에서 뺀다.
		// 언제까지냐면 sum >= K일 때 계속.
		// Two 포인터랑 비슷한 논리인데, 그걸 큐에 적용

		for (int i = 0; i < N; i++) {
			newSignal = rng.next();

			Q.push(newSignal);
			sum += newSignal;

			while (sum > K && !Q.empty()) {;
				sum -= Q.front();
				Q.pop();
			}

			if (sum == K) cnt++;

		}

		printf("%d\n", cnt);

	}

}
