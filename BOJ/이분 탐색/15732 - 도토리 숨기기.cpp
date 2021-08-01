#include <cstdio>
#include <algorithm>

int N, K, D;
int A[10000], B[10000], C[10000];

int main() {
	scanf("%d %d %d", &N, &K, &D);
	for (int i = 0; i < K; i++) {
		// A번 상자부터 B번 상자까지 C개 간격으로,
		// 도토리를 하나씩 넣는다.
		scanf("%d %d %d", A + i, B + i, C + i);
	}

	// 가장 마지막 상자 번호를 X라고 하자.
	// 그럼 K개의 규칙들을 돌면서,
	// A부터 시작해서, C개 간격으로 놓다가 X를 초과하면 break;
	
	int lo = 0, hi = N + 1;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		// mid번째가 마지막 상자 번호라고 가정하자.

		long long sum = 0; // 총 도토리를 계산한다.

		for (int i = 0; i < K; i++) {
			int start = A[i];
			int end = B[i];
			int dist = C[i];

			// start부터, start + dist, start + 2*dist..
			// start + dist*X > mid
			// 이 X를 구해야 한다.
			if (mid >= end) {
				// 그럼 이 안에 있는 건 다 들어갈 수 있다.
				sum += ((end - start) / dist + 1);
			}
			else if (mid >= start) {
				sum += ((mid - start) / dist + 1);
			}
		}

		// 이제 mid를 마지막으로 한다고 했을 때 도토리의 총 개수를 구한 상태.
		// 너무 많이 넣었다면, 마지막 번호를 당겨야 함.
		if (sum >= D) {
			hi = mid;
		} else lo = mid;
	}
	printf("%d\n", hi);

}