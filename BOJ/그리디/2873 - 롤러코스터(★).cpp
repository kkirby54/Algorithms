#include <cstdio>

// MAP을 체스판처럼 생각한다.
// OXOXOXOX
// XOXOXOXO
// OXOXOXOX
// XOXOXOXO
// OXOXOXOX
// XOXOXOXO

int map[1005][1005];

int main() {
	int R, C;
	scanf("%d %d", &R, &C);

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// 짝수
	if (R % 2 == 0) {
		// 짝수
		if (C % 2 == 0) {
			
			// 일단 X로 표시된 애들 중 최소인 애의 좌표를 찾는다.
			int min_r = 0, min_c = 0;
			int val = 10000;
			
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					if ((i + j) % 2 == 1) {
						if (map[i][j] < val) {
							val = map[i][j];
							min_r = i, min_c = j;
						}
					}

				}
			}

			// 이제 그 좌표 빼고 다 돌 수 있다.
			
			// 1. (0,0)에서 시작한다.
			int cur_r = 0, cur_c = 0;
			while (cur_r + 1 < min_r) {
				// 이동한다.
				
				// c만큼 R
				for (int k = 0; k < C-1; k++) printf("R");
				printf("D");
				for (int k = 0; k < C - 1; k++) printf("L");
				printf("D");

				cur_r += 2;
			}

			while (cur_c + 1 < min_c) {
				printf("DRUR");
				cur_c += 2;
			}

			// 그럼 2가지 케이스
			// O!  OX
			// XO  !O

			// 1번
			if (min_c == cur_c + 1) {
				printf("DR");
				cur_c += 1;
			}
			// 2번
			else {
				printf("RD");
				cur_c += 1;
			}

			while (cur_c != C - 1) {
				printf("RURD");
				cur_c += 2;
			}

			// 이제 내려가기만 하면 됨.
			while (cur_r + 1 < R - 1) {
				printf("D");
				for (int k = 0; k < C - 1; k++) printf("L");
				printf("D");
				for (int k = 0; k < C - 1; k++) printf("R");

				cur_r += 2;
			}

		}

		// 홀수
		if (C % 2 == 1) {

			for (int i = 0; i < C / 2; i++) {
				// 내려가
				for (int j = 0; j < R - 1; j++) {
					printf("D");
				}

				// 오른쪽
				printf("R");

				// 올라가
				for (int j = 0; j < R - 1; j++) {
					printf("U");
				}

				// 오른쪽
				printf("R");

			}
			for (int i = 0; i < R - 1; i++) {
				printf("D");
			}
		}

	}
	// R이 홀수
	else {
		for (int i = 0; i < R / 2; i++) {
			for (int j = 0; j < C - 1; j++) {
				printf("R");
			}
			printf("D");
			for (int j = 0; j < C - 1; j++) {
				printf("L");
			}
			printf("D");
		}

		for (int i = 0; i < C - 1; i++) {
			printf("R");
		}



	}


}