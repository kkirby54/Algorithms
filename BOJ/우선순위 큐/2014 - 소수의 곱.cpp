#include <cstdio>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

int K, N, primes[100];

int main() {
	scanf("%d %d", &K, &N);

	priority_queue<int, vector<int>, greater<int>> minHeap;
	for (int i = 0; i < K; i++) {
		scanf("%d", primes + i);
		minHeap.push(primes[i]);
	}

	int cnt = 0;
	int prev = -1;
	while (cnt < N) {
		int curr = minHeap.top();

		for (int i = 0; i < K; i++) {
			long long val = (long long) curr * primes[i];
			if (val > INT_MAX) continue;

			minHeap.push(int(val));
		}

		while (prev == minHeap.top()) {
			minHeap.pop();
		}

		prev = minHeap.top();
		cnt++;
	}
	printf("%d", minHeap.top());

}