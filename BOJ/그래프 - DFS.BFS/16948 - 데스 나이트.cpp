#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> P;

int dr[] = { -2,-2,0,0,2,2 };
int dc[] = { -1,1,-2,2,-1,1 };

int N, r1, c1, r2, c2;
bool visited[201][201];

int main() {
	scanf("%d %d %d %d %d", &N, &r1, &c1, &r2, &c2);

	// r1,c1에서 시작.
	// r2,c2로 도착한다.

	// 이동할 수 없는 경우에는 -1 출력.
	queue<P> Q;
	Q.push(P(r1, c1));
	visited[r1][c1] = true;
	int level = 0;

	while (!Q.empty()) {
		int qSize = Q.size();
		for (int k = 0; k < qSize; k++) {

			int currR = Q.front().first;
			int currC = Q.front().second;
			Q.pop();

			if (currR == r2 && currC == c2) {
				printf("%d", level);
				return 0;
			}

			for (int i = 0; i < 6; i++) {
				int nR = currR + dr[i];
				int nC = currC + dc[i];

				if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
				if (visited[nR][nC]) continue;

				visited[nR][nC] = true;
				Q.push(P(nR, nC));
			}

		}

		level++;
	}
	
	printf("-1");

}