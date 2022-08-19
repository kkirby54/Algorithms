#include <cstdio>
#include <algorithm>

int N;
int W[10];
bool isUsed[10];

int tmpVal;
int ret;

void backtrack(int cnt) {
	// 항상 N-2번이 가능하다. (가장 왼쪽, 오른쪽 제외)
	if (cnt == N-2) {
		ret = std::max(ret, tmpVal);
		return;
	}

	// 사실 결과를 보자면, 가장 왼쪽과 오른쪽을 제외한 수들을
	// 순서 있게 나열하는 방법(순열)
	for (int i = 1; i < N-1; i++) {
		if (isUsed[i]) continue;
		
		int left = i - 1, right = i + 1;

		while (isUsed[left]) left--;
		while (isUsed[right]) right++;

		tmpVal += (W[left] * W[right]);

		isUsed[i] = true;
		backtrack(cnt + 1);
		isUsed[i] = false;

		tmpVal -= W[left] * W[right];
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", W + i);
	}

	backtrack(0);

	printf("%d\n", ret);

}