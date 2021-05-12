#include <cstdio>
#include <stack>

int main() {
	int N, m;
	std::stack<int> S;
	scanf("%d", &N);

	while (1) {
		S.push(N % 2 == 0 ? 0 : 1);

		m = N / -2;
		if (N < 0 && N % 2 != 0) m++;
		N = m;

		if (!N) break;
	}

	while (!S.empty()) {
		printf("%d", S.top());
		S.pop();
	}

}