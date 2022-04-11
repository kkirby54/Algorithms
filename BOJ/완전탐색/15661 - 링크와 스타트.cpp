#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int INF = 987654321;

int N, board[20][20];
vector<int> team1, team2;

int ret = INF;

void backtrack(int curr) {
	if (curr == N) {
		if (team1.empty() || team2.empty()) return;

		// team1을 돌면서 계산한다.
		int team1Score = 0;
		for (int i : team1) {
			for (int j : team1) {
				team1Score += board[i][j];
			}
		}

		int team2Score = 0;
		for (int i : team2) {
			for (int j : team2) {
				team2Score += board[i][j];
			}
		}

		ret = min(ret, abs(team2Score - team1Score));

		return;
	}

	// curr을 team1에 넣을 수도, 2에 넣을 수도 있다.
	team1.push_back(curr);
	backtrack(curr + 1);
	team1.pop_back();

	// team2에 넣는다.
	team2.push_back(curr);
	backtrack(curr + 1);
	team2.pop_back();


}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	backtrack(0);

	printf("%d", ret);
}