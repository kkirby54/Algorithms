// kks227의 풀이를 참고 - 21.07.31

#include <cstdio>
#include <set>
#include <algorithm>

typedef std::pair<int, int> P;

int N, nums;
int board[21][21]; // 1은 불순물, 2는 보석

int solve(int r1, int c1, int r2, int c2, int way) {
	if (r1 > r2 || c1 > c2) return 0;

	int gems = 0, problems = 0;
	P problemsLoc[400];

	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			if (board[i][j] == 2) gems++;
			else if (board[i][j] == 1) {
				problemsLoc[problems++] = P(i, j);
			}
		}
	}
	if (gems == 0) return 0;
	if (gems == 1) return !problems;
	if (problems == 0) return 0;

	int result = 0;

	// 이제 여기에 속한 불순물, 보석을 다 확인함.
	// 이전에 자른 거가 지금에 영향을 준다.
	
	// 세로로 잘라버리기.
	if (way != 2) {
		// 모든 problems에 대해서
		for (int k = 0; k < problems; k++) {
			bool isPossible = true;
			auto pC = problemsLoc[k].second;

			// 잘랐는데 가능하냐?
			for (int i = r1; i <= r2; i++) {
				// 얘가 2이면 불가능함 자르는게.
				if (board[i][pC] == 2) {
					isPossible = false;
					break;
				}
			}
			// 가능하다면 자르고 재귀
			if (isPossible) {
				result += solve(r1, c1, r2, pC-1, 2) *
					solve(r1, pC + 1, r2, c2, 2);
			}

		}
	}

	if (way != 1) {
		for (int k = 0; k < problems; k++) {
			bool isPossible = true;
			auto pR = problemsLoc[k].first;

			for (int i = c1; i <= c2; i++) {
				if (board[pR][i] == 2) {
					isPossible = false;
					break;
				}
			}
			if (isPossible) {
				result += solve(r1, c1, pR-1, c2, 1) *
					solve(pR + 1, c1, r2, c2, 1);
			}
		}
	}

	return result;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}
	int ret = solve(0, 0, N - 1, N - 1, 0);
	printf("%d\n", ret ? ret : -1);

}