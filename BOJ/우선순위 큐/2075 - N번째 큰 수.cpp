#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int N, num;

int main() {
	scanf("%d", &N);
	priority_queue<int, vector<int>, greater<int>> minHeap;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &num);
			minHeap.push(num);
		}
		while (minHeap.size() > N) minHeap.pop();
	}

	printf("%d", minHeap.top());
}