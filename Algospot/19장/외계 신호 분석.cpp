#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>

const long long MOD = (long long)pow(2, 32);

int C, N, K, input;

int main() {
	scanf("%d", &C);

	for (int i = 0; i < C; i++) {
		scanf("%d %d", &K, &N);

		long long tmp;
		std::queue<int> Q;

		int sum = 0, cnt = 0;

		// 큐에 일단 넣고 본다.
		// 넣은 다음에
		// sum의 크기에 따라 다르다.
		// 1. sum == K. cnt++, 그리고 큐에 있는거 하나 빼기
		// 2. sum < K. 이러면 그냥 continue;
		// 3. sum > K. 그럼 큐에서 뺀다.
		// 언제까지냐면 sum >= K일 때 계속.
		// Two 포인터랑 비슷한 논리인데, 그걸 큐에 적용

		tmp = 1983;
		for (int i = 0; i < N; i++) {
			input = tmp % 10000 + 1;
			tmp = ((tmp % MOD) * 214013 + 2531011) % MOD;

			Q.push(input);
			sum += input;

			while (sum >= K && !Q.empty()) {
				if (sum == K) cnt++;
				sum -= Q.front();
				Q.pop();
			}
		}

		printf("%d\n", cnt);

	}

}
