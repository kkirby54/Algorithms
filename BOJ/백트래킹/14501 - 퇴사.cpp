#include <cstdio>
#include <algorithm>

int N;
int T[15], P[15];
int tmp, maxVal;

void backtrack(int curr) {
	if (curr >= N) {
		maxVal = std::max(maxVal, tmp);
		return;
	}

	// curr일을 택하지 않는다.
	backtrack(curr + 1);

	// curr일을 택한다. 단, 더해서 N+1 이상이 되면 안됨.
	if (curr + T[curr] <= N) {
		tmp += P[curr];
		backtrack(curr + T[curr]);
		tmp -= P[curr];
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", T + i, P + i);
	}

	// T[i]일이 걸리고, 금액은 P[i].
	backtrack(0);

	printf("%d\n", maxVal);
}