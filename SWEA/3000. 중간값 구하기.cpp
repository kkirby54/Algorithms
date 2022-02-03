#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int T, N, A, X, Y;

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &A);

		priority_queue<int, vector<int>, greater<int>> minHeap;
		priority_queue<int> maxHeap;

		minHeap.push(A);
		int ret = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 2; j++) {
				scanf("%d", &X);

				// minHeap.top과의 비교
				int pivot = minHeap.top();

				if (X > pivot)
					minHeap.push(X);
				else maxHeap.push(X);
			}
		
			while (minHeap.size() > maxHeap.size() + 1) {
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}

			while (maxHeap.size() > minHeap.size()) {
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}

			ret += (minHeap.top());
			ret %= 20171109;
		}
		

		printf("#%d %d\n", t, ret);
	}

}