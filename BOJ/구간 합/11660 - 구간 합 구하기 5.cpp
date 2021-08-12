#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int pSum[1025][1025];
int main() {
	int N, M, num, x1,y1,x2,y2;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &num);
			pSum[i + 1][j + 1] =
				pSum[i][j + 1] + pSum[i + 1][j] - pSum[i][j] + num;
		}
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		printf("%d\n", pSum[x2][y2] - pSum[x2][y1-1] - pSum[x1-1][y2] + pSum[x1 - 1][y1 - 1] );
	}

}