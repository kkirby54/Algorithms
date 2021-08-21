#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;

int directions[] = { -1,1,-3,3 };
string num;
string goal = "123456780";
set<string> visited;

int main() {
	string start;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> num;
			start += num;
		}
	}
	
	queue<string> Q;
	visited.insert(start);
	Q.push(start);

	int ret = 0;
	while (!Q.empty()) {
		int qSize = Q.size();
		for (int i = 0; i < qSize; i++) {
			string curr = Q.front();
			Q.pop();

			if (curr == goal) {
				cout << ret;
				return 0;
			}

			// 0의 위치를 찾는다.
			int zeroIndex = 0;
			for (int i = 0; i < 9; i++) {
				if (curr[i] == '0') {
					zeroIndex = i;
					break;
				}
			}

			for (int j = 0; j < 4; j++) {
				if (zeroIndex % 3 == 0 && j == 0) continue;
				if (zeroIndex % 3 == 2 && j == 1) continue;

				int next = zeroIndex + directions[j];
				if (next < 0 || next > 9) continue;

				swap(curr[next], curr[zeroIndex]);
				if (visited.find(curr) == visited.end()) {
					Q.push(curr);
					visited.insert(curr);
				}
				swap(curr[next], curr[zeroIndex]);
			}

		}

		ret++;
	}
	cout << "-1";

}