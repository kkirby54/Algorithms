#include <cstdio>
#include <stack>

int main() {
	int A, B, m;
	std::stack<int> S;
	int arr[26];

	scanf("%d %d %d", &A, &B, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", arr + i);
	}

	// A진법을 일단 10진법으로
	int ret = 0, k = 1;
	for (int i = m - 1; i >= 0; i--) {
		ret += arr[i] * k;
		k *= A;
	}

	// ret를 B진법으로 바꾼다.
	while (ret) {
		S.push(ret % B);
		ret /= B;
	}

	while (!S.empty()) {
		printf("%d ", S.top());
		S.pop();
	}

}