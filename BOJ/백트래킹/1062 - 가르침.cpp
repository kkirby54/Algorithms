#include <cstdio>
#include <algorithm>
#include <vector>

int N, K;
char word[51][16];

char alphabet[30];
int alphaCnt;

bool isUsed[30];
int maxVal;

void backtrack(int curr, int cnt) {
	if (curr >= alphaCnt) {
		if (cnt != K) return;
	}

	if (cnt == K) {
		bool easyUsed[30] = { 0 };

		for (int i = 0; i < alphaCnt; i++) {
			if (isUsed[i]) {
				easyUsed[alphabet[i] - 'a'] = true;
			}
		}

		int tmpVal = 0;
		// 이 알파벳들을 가지고 계산해본다.
		for (int i = 0; i < N; i++) {


			bool isPossible = true;
			for (int j = 0; word[i][j]; j++) {

				if (!easyUsed[word[i][j] - 'a']) {
					isPossible = false;
					break;
				}
			}

			if (isPossible) {
				tmpVal++;
			}
		}

		if (maxVal < tmpVal) {
			maxVal = tmpVal;
		}

		//puts("");
		return;
	}


	isUsed[curr] = true;
	backtrack(curr + 1, cnt + 1);
	isUsed[curr] = false;

	backtrack(curr + 1, cnt);

}

int main() {
	scanf("%d %d", &N, &K);

	alphabet[0] = 'a';
	alphabet[1] = 't';
	alphabet[2] = 'n';
	alphabet[3] = 'c';
	alphabet[4] = 'i';
	alphaCnt = 5;

	for (int i = 0; i < N; i++) {
		scanf("%s", word[i]);
		for (int j = 0; word[i][j]; j++) {
			
			bool isExisit = false;
			for (int k = 0; k < alphaCnt; k++) {
				if (word[i][j] == alphabet[k]) {
					isExisit = true;
					break;
				}
			}

			if (!isExisit) {
				alphabet[alphaCnt++] = word[i][j];
			}

		}
	}

	isUsed[0] = true;
	isUsed[1] = true;
	isUsed[2] = true;
	isUsed[3] = true;
	isUsed[4] = true;
	// a, t, n, c, i는 반드시 있어야 함.

	if (K < 5) {
		puts("0");
	}
	// 더 많이 가르치는 경우는 N개 모두 가능.
	else if (K >= alphaCnt) {
		printf("%d\n", N);
	}
	else {
		backtrack(5, 5);

		printf("%d\n", maxVal);

	}


}