#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int C, N, num;

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);

		priority_queue<int, vector<int>, greater<int>> min_heap;
		priority_queue<int> max_heap;
		vector<int> ret;

		for (int i = 0; i < N; i++) {
			scanf("%d", &num);

			if (max_heap.size() == min_heap.size())
				max_heap.push((int)num);
			else
				min_heap.push((int)num);

			// 바꾸기
			if (!max_heap.empty() && !min_heap.empty()) {
				if (max_heap.top() > min_heap.top()) {
					int maxTop = max_heap.top();
					int minTop = min_heap.top();

					max_heap.pop();
					min_heap.pop();
					min_heap.push(maxTop);
					max_heap.push(minTop);
				}
			}

			if (i % 2 == 0) {
				ret.push_back(max_heap.top());
			}
		}

		printf("%d\n", ret.size());
		for (int i = 1; i <= ret.size(); i++) {
			printf("%d", ret[i-1]);
			if (i % 10 == 0) puts("");
			else printf(" ");
		}
		puts("");
	}

}

