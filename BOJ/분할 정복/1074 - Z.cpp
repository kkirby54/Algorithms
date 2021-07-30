#include <cstdio>
#include <cmath>
#include <algorithm>

int N, R, C;
int ret;

void Z(int r, int c, int size) {
	if (size == 1) {
		//ret++;
		return;
	}

	int nSize = size / 2;
	
	if (r + nSize > R) {
		// 1번째 구간에 있을 때
		if (c + nSize > C) {
			Z(r, c, nSize);
		}
		// 2번째 구간에 있을 때
		else {
			ret += nSize * nSize;
			Z(r, c + nSize, nSize);
		}
	}
	else {
		// 3번째 구간에 있을 때
		if (c + nSize > C) {
			ret += nSize * nSize * 2;
			Z(r + nSize, c, nSize);
		}
		else {
			ret += nSize * nSize * 3;
			Z(r + nSize, c + nSize, nSize);
		}
	}

}

int main() {
	scanf("%d %d %d", &N, &R, &C);

	Z(0, 0, (int)pow(2, N));
	printf("%d\n", ret);
}