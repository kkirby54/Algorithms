#include <cstdio>
#include <stack>
#include <vector>

int C, N;

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		std::stack<int> remaining;
		std::vector<int> H(N);
	
		for (int i = 0; i < N; i++) {
			scanf("%d", &H[i]);
		}
		H.push_back(0);

		int ret = 0;
		for (int i = 0; i < H.size(); i++) {

			while (!remaining.empty() &&
				H[remaining.top()] >= H[i]) {
				
				// 계속 깎아내기.
				int j = remaining.top();
				remaining.pop();
				
				int width = -1;
				if (remaining.empty())
					width = i;
				else
					width = (i - remaining.top() - 1);

				ret = std::max(ret, width * H[j]);
			}
			remaining.push(i);
		}

		printf("%d\n", ret);
	}

}