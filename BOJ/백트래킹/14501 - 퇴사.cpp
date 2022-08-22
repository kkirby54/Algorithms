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

	// curr���� ������ �ʴ´�.
	backtrack(curr + 1);

	// curr���� ���Ѵ�. ��, ���ؼ� N+1 �̻��� �Ǹ� �ȵ�.
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

	// T[i]���� �ɸ���, �ݾ��� P[i].
	backtrack(0);

	printf("%d\n", maxVal);
}