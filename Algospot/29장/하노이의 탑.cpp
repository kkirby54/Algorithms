#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int C, N;

// index에 있는 애가 몇번째 기둥에 속했는지 (0,1,2,3 중 하나임)
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}

int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
int incr(int x) { if (x < 0) return x - 1; else return x + 1; }

// 정수로 표현한 상태를 저장 like map
int c[1 << (12 * 2)];

// start부터 finish까지.
int bfs(int start, int finish) {
	if (start == finish) return 0;

	queue<int> Q;
	Q.push(start);
	Q.push(finish);

	//int level = 0;
	c[start] = 1;
	c[finish] = -1;

	while (!Q.empty()) {
		int here = Q.front();
		Q.pop();

		// 일단은 다 찾아놔.
		int top[4] = { -1, -1, -1, -1 };
		for (int i = 0; i < N; i++) {
			int val = get(here, i);
			if (top[val] == -1) top[val] = i;
		}

		// 그 다음. i번째->j번쨰 기둥 swap
		for (int i = 0; i < 4; i++) {
			// 근데 i번쨰 기둥에 원반이 일단 잇어야 되잖아
			if (top[i] == -1) continue;

			for (int j = 0; j < 4; j++) {
				if (i == j) continue;

				// i번째 기둥에 있는 top < j번째 기둥에 있는 top
				// 또는, j번째 기둥에 아무 것도 없다면.
				if (top[i] < top[j] || top[j] == -1) {
					int next = set(here, top[i], j);

					// 그리고, j에 대한 거가
					if (c[next] == 0) {
						c[next] = incr(c[here]);
						Q.push(next);
					}
					else if (sgn(c[here]) != sgn(c[next])) {
						//printf("몇트냐? %d\n", c[here] + 1);
						return abs(c[here]) + abs(c[next]) - 1;
					}
				}

			}
		}
	}
	return -1;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		// 여기에 저장한다.
		int start = 0, finish = 0;
		memset(c, 0, sizeof(c));

		for (int i = 0; i < 4; i++) {
			// i번째 기둥에 대해서 기록

			int num, disk;
			scanf("%d", &num);
			for (int j = 0; j < num; j++) {
				scanf("%d", &disk);
				start = set(start, disk - 1, i);
			}
		}

		// finish는?
		// 3에 몰려
		for (int i = 0; i < N; i++) {
			finish = set(finish, i, 3);
		}

		/*
		for (int i = 0; i < 4; i++) {
			int num, disk;
			scanf("%d", &num);
			for (int j = 0; j < num; j++) {
				scanf("%d", &disk);
				finish = set(finish, disk, i);
			}
		}
		*/

		/*
		printf("초기 상태 : 0x%x\n", start);
		for (int i = 1; i <= N; i++)
			printf("%d번째 : %d에 있음\n", i, get(start, i));

		*/

		printf("%d\n", bfs(start, finish));
	}
}