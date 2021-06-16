#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int C, N, a, b;
long long curr;

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d %d", &N, &a, &b);

		priority_queue<int> max_heap;
		priority_queue<int, vector<int>, greater<int>> min_heap;

		long long sum = 0;
		// 조건
		// 일단 최대힙에 작은 수들,
		// 최소힙에 큰 수들이 들어간다.

		// 최대힙에 하나가 더 들어간다.
		// 홀수일 때 살펴보면.. 총 7개라 햇을때
		// 최대힙에 4개, 최소힙에 3개가 들어간다.
		// 그럼 그냥 최대힙의 top().

		curr = 1983;
		for (int i = 0; i < N; i++) {
			// 무조건 최대힙 원소 <= 최소힙 원소
			// max_heap.top() <= min_heap.top()
			// max_heap.size()는 min_heap.size()보다 같거나 1 큼.

			if (max_heap.size() == min_heap.size()) {
				max_heap.push(curr);
			}
			else min_heap.push(curr);

			// 이제 최대힙 원소 <= 최소힙 원소 조건 만족 확인
			if (!max_heap.empty() && !min_heap.empty() &&
				max_heap.top() > min_heap.top()) {
				// 그럼 swap.
				int a = max_heap.top(), b = min_heap.top();
				max_heap.pop(), min_heap.pop();
				max_heap.push(b); min_heap.push(a);
			}

			// 그리고 무조건 최대힙의 원소
			sum += max_heap.top();
			sum %= 20090711;
			curr = (curr * a + b) % 20090711;
		}

		printf("%lld\n", sum);
	}

}