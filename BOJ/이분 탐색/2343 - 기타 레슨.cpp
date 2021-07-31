#include <cstdio>
#include <algorithm>

int N, M, maxVal;
int lessons[100000];

// 블루레이 크기 = X라고 했을 때,
// lessons를 잘라서 나오는 블루레이의 개수
int getBluray(int X) {
	int sum = 0;
	int ret = 1; // 일단 처음에 하나는 넣어야 하니까.
	for (int i = 0; i < N; i++) {
		// 만약 하나만으로 X를 초과하면 애초에 못 넣음
		if (lessons[i] > X) return 987654321;
		sum += lessons[i];
		// 초과한다면 
		if (sum > X) {
			sum = lessons[i];
			ret++;
		}
	}

	return ret;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", lessons + i);
	}

	int lo = 0, hi = 1000000000;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		// mid 길이로 자른다고 하자.
		int ret = getBluray(mid);

		// ret가 M을 초과하면, 길이를 늘려서 ret를 줄여야 함.
		// ret == M이라면, hi를 취함. (최소를 구해야 함)
		if (ret > M) {
			lo = mid;
		}
		else hi = mid;
	}
	printf("%d\n", hi);
}