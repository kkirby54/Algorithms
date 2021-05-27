#include <cstdio>
#include <cmath>
#include <algorithm>

int N, M, broken;
bool button[11];

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i <= 10; i++) button[i] = true;

	for (int i = 0; i < M; i++) {
		scanf("%d", &broken);
		button[broken] = false;
	}

	int ret;
	int curr, cnt;
	bool isPossible = false;

	// 그냥 +-로
	ret = abs(N - 100);

	for (int i = 0; i <= 1000005; i++) {
		// 버튼을 눌러서 curr를 갈 수 있는지
		curr = i;
		cnt = 0;

		while (1) {
			// 각 자리에 대해서 isPossible
			isPossible = false;
			for (int j = 0; j <= 10; j++) {
				if (button[j]) {
					if (j == curr % 10) {
						isPossible = true;
					}
				}
			}
			if (!isPossible) break;
			cnt++;
			curr /= 10;
			if (!curr) break;
		}
		if (!isPossible) continue;

		ret = std::min(ret, abs(N - i) + cnt);
	}



	printf("%d", ret);
}