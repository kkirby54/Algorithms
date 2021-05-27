#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>

const std::function<int(int)> func[4] = {
	[](int n) {return n * 2 % 10000; },
	[](int n) {return n == 0 ? 9999 : n - 1; },
	[](int n) {return (n * 10) % 10000 + n / 1000; },
	[](int n) { return (n % 10) * 1000 + n / 10; }
};

int prev[10000], op[10000];

int main() {
	int T;
	char c[4] = { 'D', 'S', 'L', 'R' };
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		int A, B;
		scanf("%d %d", &A, &B);
		std::fill(prev, prev + 10000, -1);
		std::fill(op, op + 10000, -1);

		std::queue<int> Q;
		Q.push(A);

		while (prev[B] == -1) {
			int curr = Q.front();
			Q.pop();
			//printf("%d 도착\n", curr);

			for (int i = 0; i < 4; i++) {
				int next = func[i](curr);

				if (prev[next] == -1) {
					prev[next] = curr;
					op[next] = c[i];
					Q.push(next);
				}
			}
		}

		std::stack<char> S;
		while (B != A) {
			S.push(op[B]);
			B = prev[B];
		}

		while (!S.empty()) {
			printf("%c", S.top());
			S.pop();
		}
		puts("");
	}

}