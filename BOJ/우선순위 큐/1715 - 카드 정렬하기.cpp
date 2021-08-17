#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int N, num, sum;

int main() {
	scanf("%d", &N);
	priority_queue<int, vector<int>, greater<int>> minHeap;

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		minHeap.push(num);
	}

	while (minHeap.size() != 1) {
		// 두개를 뺸다.
		int fVal = minHeap.top(); minHeap.pop();
		int sVal = minHeap.top(); minHeap.pop();

		sum += (fVal + sVal);
		minHeap.push(fVal + sVal);
	}

	printf("%d\n", sum);
}