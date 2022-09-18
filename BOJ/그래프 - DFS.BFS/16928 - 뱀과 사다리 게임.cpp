#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, x, y, u, v;
int ladder[101], snake[101];
bool visited[101];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);

		ladder[x] = y;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		snake[u] = v;
	}

	// 1������ �����Ѵ�.
	queue<int> Q;
	Q.push(1);
	visited[1] = true;

	int level = 0;

	while (!Q.empty()) {
		int qSize = Q.size();
		while (qSize--) {
			int curr = Q.front();
			Q.pop();

			if (curr == 100) {
				printf("%d\n", level);
				return 0;
			}

			bool isNaive = true;
			// �ֻ����� ������.
			for (int i = 1; i <= 6; i++) {
				if (curr + i > 100) break;

				// ��ٸ����
				if (ladder[curr + i] != 0) {
					isNaive = false;
					if (!visited[ladder[curr + i]]) {
						visited[ladder[curr + i]] = true;
						Q.push(ladder[curr + i]);
						
					}
				}
				// ���̶��
				if (snake[curr + i] != 0) {
					isNaive = false;
					if (!visited[snake[curr + i]]) {
						visited[snake[curr + i]] = true;
						Q.push(snake[curr + i]);
					}
				}

			}

			// ��, ��ٸ� �ƹ� �͵� ���ٸ� �׳� 6�� ����.
			if (isNaive) {
				int next = curr + 6;
				if (next >= 100) next = 100;
				Q.push(next);
				visited[next] = true;
			}
			else {
				for (int i = 1; i <= 6; i++) {
					if (curr + i > 100) break;

					// curr + i��ŭ �����δ�.
					if (ladder[curr + i] == 0 && snake[curr + i] == 0) {
						if (!visited[curr + i]) {
							Q.push(curr + i);
							visited[curr + i] = true;
						}
					}

				}

			}


		}
		level++;


	}

	


}