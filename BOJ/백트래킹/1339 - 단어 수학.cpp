#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int N;
char words[10][9];
vector<char> candi;
int candiSize;
bool used[10];

int val[26];
int ret = -1;

void backtrack(int curr) {
	if (curr == candiSize) {
		// N개의 단어에 대해 계산.
		int sum = 0;
		for (int i = 0; i < N; i++) {
			int tmp = 0;
			for (int j = 0; words[i][j]; j++) {
				tmp += val[words[i][j] - 'A'];
				if (words[i][j+1]) tmp *= 10;
			}
			sum += tmp;
		}
		ret = max(ret, sum);
		return;
	}

	for (int i = 0; i < 10; i++) {
		int alpha = candi[curr] - 'A';

		if (used[i]) continue;
		used[i] = true;
		// candi[i]의 val를 i로 둔다.
		val[alpha] = i;

		backtrack(curr + 1);

		used[i] = false;
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", words[i]);
		for (int j = 0; words[i][j]; j++) {
			if (find(candi.begin(), candi.end(), words[i][j]) == candi.end()) {
				candi.push_back(words[i][j]);
			}
		}
	}
	candiSize = candi.size();
	backtrack(0);

	printf("%d", ret);
}