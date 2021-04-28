#include <cstdio>
#include <queue>
#include <stack>
#include <algorithm>

typedef std::pair<int, char> P;

int main() {
	int T, A, B, curr_t;
	scanf("%d", &T);

	int digits[4];

	for (int t = 0; t < T; t++) {
		scanf("%d %d", &A, &B);

		bool visited[10000] = { 0 };
		P prev[10000];
		std::queue<int> Q;
		Q.push(A);
		visited[A] = true;

		int curr, next;
		int level = 0;
		while (!Q.empty()) {

			int qSize = Q.size();
			//printf("======%d=====\n", level);
			for (int i = 0; i < qSize; i++) {
				curr = Q.front();
				Q.pop();

				if (curr == B) {
					//printf("%d만에 옴\n", level);
					break;
				}

				// D연산
				next = curr * 2 % 10000;
				if (!visited[next]) {
					visited[next] = true;
					Q.push(next);
					prev[next] = P(curr, 'D');
				}

				// S연산
				if (curr == 0 && !visited[9999]) {
					visited[9999] = true;
					Q.push(9999);
					prev[9999] = P(curr, 'S');
				}
				if (curr - 1 >= 0 && !visited[curr - 1]) {
					visited[curr - 1] = true;
					Q.push(curr - 1);
					prev[curr - 1] = P(curr, 'S');
				}

				// 자릿수 구하기
				curr_t = curr;
				for (int j = 0; j < 4; j++) {
					digits[j] = curr_t % 10;
					curr_t /= 10;
				}

				// L연산, R연산
				int L_curr = digits[0] * 10 + digits[1] * 100 + digits[2] * 1000 + digits[3];
				int R_curr = digits[0] * 1000 + digits[1] + digits[2] * 10 + digits[3] * 100;

				if (!visited[L_curr]) {
					visited[L_curr] = true;
					Q.push(L_curr);
					prev[L_curr] = P(curr, 'L');
				}
				if (!visited[R_curr]) {
					visited[R_curr] = true;
					Q.push(R_curr);
					prev[R_curr] = P(curr, 'R');
				}
			}
			if (curr == B) break;

			level++;
		}

		std::stack<int> S;

		// prev 배열.
		for (int k = 0; k < level; k++) {
			S.push(prev[B].second);
			//printf("%d이고, %d연산\n", prev[B].first, prev[B].second);
			B = prev[B].first;
		}

		while (!S.empty()) {
			printf("%c", S.top());
			S.pop();
		}
		puts("");

	}
}