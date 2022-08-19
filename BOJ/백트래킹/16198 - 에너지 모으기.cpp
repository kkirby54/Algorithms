#include <cstdio>
#include <algorithm>

int N;
int W[10];
bool isUsed[10];

int tmpVal;
int ret;

void backtrack(int cnt) {
	// �׻� N-2���� �����ϴ�. (���� ����, ������ ����)
	if (cnt == N-2) {
		ret = std::max(ret, tmpVal);
		return;
	}

	// ��� ����� ���ڸ�, ���� ���ʰ� �������� ������ ������
	// ���� �ְ� �����ϴ� ���(����)
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