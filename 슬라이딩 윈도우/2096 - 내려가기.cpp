#include <cstdio>
#include <cstring>
#include <algorithm>

int main() {
	int N;
	int tempMax[3], tempMin[3];
	int colMax[3] = { 0 }, colMin[3] = { 0 };

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", tempMax + j);
			tempMin[j] = tempMax[j];
			tempMax[j] += std::max(colMax[1], (j == 1) ? std::max(colMax[0], colMax[2]) : colMax[j]);
			tempMin[j] += std::min(colMin[1], (j == 1) ? std::min(colMin[0], colMin[2]) : colMin[j]);
		}

		// Col을 갱신.
		memcpy(colMax, tempMax, sizeof(int) * 3);
		memcpy(colMin, tempMin, sizeof(int) * 3);
	}
	std::sort(colMax, colMax + 3);
	std::sort(colMin, colMin + 3);

	printf("%d %d", colMax[2], colMin[0]);
}