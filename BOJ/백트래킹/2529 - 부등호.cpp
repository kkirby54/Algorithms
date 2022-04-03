#include <iostream>
#include <string>
#include <algorithm>

int K, ret[11];
bool used[10];
char a, A[10];
std::string minStr = "99999999", maxStr = "000000000";

void backtrack(int curr) {
	if (curr == K) {
		std::string tmp;

		for (int i = 0; i <= K; i++)
			tmp.push_back(ret[i] + '0');

		minStr = std::min(minStr, tmp);
		maxStr = std::max(maxStr, tmp);
	}

	char opr = A[curr];
	int currVal = ret[curr];
	if (opr == '<') {
		// currVal보다 큰 값을 넣는다.
		for (int i = currVal + 1; i < 10; i++) {
			if (used[i]) continue;

			ret[curr + 1] = i;
			used[i] = true;
			backtrack(curr + 1);
			ret[curr + 1] = 0;
			used[i] = false;
		}
	}
	else {
		for (int i = 0; i < currVal; i++) {
			if (used[i]) continue;

			ret[curr + 1] = i;
			used[i] = true;
			backtrack(curr + 1);
			ret[curr + 1] = 0;
			used[i] = false;
		}
	}

}

int main() {
	std::cin >> K;

	for (int i = 0; i < K; i++) {
		std::cin >> A[i];
	}

	// 초기값은 0,1,~9.
	for (int i = 0; i < 10; i++) {
		ret[0] = i;
		used[i] = true;
		backtrack(0);
		used[i] = false;
	}

	std::cout << maxStr << "\n";
	std::cout << minStr << "\n";
}