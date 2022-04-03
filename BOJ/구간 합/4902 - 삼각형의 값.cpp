#include <cstdio>
#include <algorithm>
#include <cstring>
int T;
int N;
int board[405][805] = { 0 };

// i번째 행에 대해서 부분합을 저장한다.
int pSum[405][805];

int main() {
	while (++T) {
		scanf("%d", &N);
		if (N == 0) return 0;

		memset(board, 0, sizeof(board));
		memset(pSum, 0, sizeof(pSum));
		int maxVal = -987654321;

		for (int i = 0; i < N; i++) {
			// i번쨰는 2*i + 1 개의 입력을 받는다.
			for (int j = 0; j < 2 * i + 1; j++) {
				scanf("%d", &board[i][j]);
				pSum[i][j + 1] = pSum[i][j] + board[i][j];
				maxVal = std::max(maxVal, board[i][j]);
			}
		}


		// i,j를 기준으로 삼각형
		for (int i = 0; i < N - 1; i++) {
			for (int j = 0; j <= 2 * i; j += 2) {
				// i,j가 정해지면, 거기서부터 밑으로 내려가며 파야한다.
				int sum = board[i][j];
				// 이만큼 더하면, 삼각형이 결정된다.
				for (int k = 1; i + k < N; k++) {
					// board[i+k][j] ~ board[i+k][j + 2*k]를 다 더한다.
					sum += (pSum[i + k][j + 2 * k + 1] - pSum[i + k][j]);
					maxVal = std::max(maxVal, sum);
				}
			}
		}

		// i, j 기준으로 역삼각형
		for (int i = 3; i < N; i++) {
			for (int cnt = 0; cnt < i-2; cnt++) {
				int j = 3 + cnt * 2;

				int sum = board[i][j];
				for (int k = 1; j - 2 * k > 0 && j <= 2* (i - k); k++) {
					
					// board[i-k][j-2*k] ~ board[i-k][j]까지.
					sum += pSum[i - k][j + 1] - pSum[i - k][j - 2 * k];

					maxVal = std::max(maxVal, sum);
				}
			}
		}

		printf("%d. %d\n", T, maxVal);
	}

}