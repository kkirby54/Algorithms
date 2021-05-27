#include <cstdio>
#include <set>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

int off[] = { -1, 1, 3, -3 };

std::set<string> S;

struct P {
	int curr;
	string s;

	P(int curr, string s) : curr(curr), s(s) {}
};

int board[3][3];
string goal = "123456780";

int main() {
	int void_curr;
	string start;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] == 0) {
				void_curr = i * 3 + j;
			}
			start += board[i][j] + '0';
		}
	}

	if (start == goal) {
		printf("0");
		return 0;
	}


	S.insert(start);
	queue<P> Q;
	Q.push(P(void_curr, start));


	int level = 0;
	while (!Q.empty()) {
		int qSize = Q.size();
		//printf("=====%d====\n", level);
		for (int i = 0; i < qSize; i++) {
			int curr = Q.front().curr;
			string temp = Q.front().s;
			Q.pop();

			for (int j = 0; j < 4; j++) {
				if (curr % 3 == 0 && j == 0) continue;
				if (curr % 3 == 2 && j == 1) continue;

				int next = curr + off[j];

				if (next < 0 || next >= 9) continue;

				// temp[next]와 temp[curr]을 바꿔
				string temp_t = temp;

				char t = temp_t[curr];
				temp_t[curr] = temp_t[next];
				temp_t[next] = t;

				// Set에 이미 있다면 꺼져
				if (S.find(temp_t) != S.end()) continue;

				// 만약 temp가 goal이라면?..
				if (temp_t == goal) {
					printf("%d", level+1);
					return 0;
				}

				S.insert(temp_t);
				Q.push(P(next, temp_t));
			}

		}
		level++;

	}
	printf("-1");

}