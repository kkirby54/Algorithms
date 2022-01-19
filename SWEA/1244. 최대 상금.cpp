#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#include <string>
#include <queue>
using namespace std;
typedef pair<string, int> P;

set<string> visited;
int T, limit, N;
int ret = 0;
bool isPossible;
string str;

void exchange(int curr, int remain) {
	if (remain % 2 == 0 || isPossible) {
		int sum = 0;
		for (int i = N - 1; i >= 0; i--) {
			sum += (str[i] - '0') * int(pow(10, N - 1 - i));
		}
		//printf("%d ����\n", sum);
		ret = std::max(ret, sum);

		if (remain == 0) return;
	}
	if (curr == N) return;

	// �� �ٲٰ� �ѱ��.
	exchange(curr + 1, remain);

	for (int i = 0; i < N; i++) {
		if (curr == i) continue;

		// curr�� i��°�� �ٲ۴�.
		std::swap(str[i], str[curr]);
		if (visited.find(str) == visited.end()) {
			visited.insert(str);
			exchange(0, remain - 1);
		}

		// ������� ������.
		std::swap(str[i], str[curr]);

	}

}

int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> str >> limit;

		N = str.length();
		ret = 0;

		isPossible = false;
		int nums[10] = { 0 };
		for (int i = 0; i < N; i++) {
			if (nums[str[i] - '0'] != 0) {
				isPossible = true;
				break;
			}
			nums[str[i] - '0']++;
		}

		for (int i = 0; i < N; i++) {
			//printf("=====%d���� �ٲٱ� ����======\n", str[i] - '0');
			visited.clear();
			exchange(i, limit);
		}


		cout << "#" << t << " " << ret << "\n";
	}

}