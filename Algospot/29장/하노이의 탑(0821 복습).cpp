#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, num, curr;

int getState(int state, int index) {
	return (state >> (2 * index)) & 3;
}

int setState(int state, int index, int value) {
	// index에 있는 값 말고 다 0인거.
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

int sgn(int x) {
	if (!x) return 0;
	return x > 0 ? 1 : -1;
}
int inc(int x) {
	return x >= 0 ? x + 1 : x - 1;
}

int c[1 << (12 * 2)];

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		memset(c, 0, sizeof(c));

		int start = 0, goal = 0;
		for (int i = 0; i < 4; i++) {
			scanf("%d", &num);
			// i번째 원판에 num개가 있다.
			for (int j = 0; j < num; j++) {
				scanf("%d", &curr);
				curr--;
				start = start | (i << (curr*2));
			}
		}

		// goal은 이 문제에서 모든 원판이 4번째 기둥에 있을 때.
		for (int i = 0; i < N; i++) {
			goal = goal | (3 << (i * 2));
		}

		if (start == goal) {
			puts("0");
			continue;
		}

		queue<int> Q;
		Q.push(start);
		Q.push(goal);
		c[start] = 1;
		c[goal] = -1;
		bool isFound = false;

		while (!Q.empty()) {
			int qSize = Q.size();
			for (int i = 0; i < qSize; i++) {
				int curr = Q.front();
				Q.pop();

				// 다른 곳으로 이동.
				// 그러려면, 각 원판에서 제일 위에 있는 걸 알아야함.
				int top[4] = { -1,-1,-1, -1 };
				for (int j = 0; j < N; j++) {
					if (top[getState(curr, j)] == -1) {
						top[getState(curr, j)] = j;
					}
				}

				// 이제 하나씩 다 바꿔본다.
				for (int from = 0; from < 4; from++) {
					// from -> to.
					if (top[from] == -1) continue;

					for (int to = 0; to < 4; to++) {
						if (top[from] < top[to] || top[to] == -1) {
							// GO!
							int next = setState(curr, top[from], to);

							if (c[next] == 0) {
								c[next] = inc(c[curr]);
								Q.push(next);
							}
							else {
								// c[curr]과 c[next] 부호가 다르면,
								if (sgn(c[curr]) != sgn(c[next])) {
									printf("%d\n", abs(c[curr]) + abs(c[next]) -1);
									isFound = true;
									break;
								}

							}
						}

					}
					if (isFound) break;
				}

				if (isFound) break;
			}
			if (isFound) break;
		}
	}

}