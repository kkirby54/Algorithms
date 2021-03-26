#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
const int INF = 1000000000;
typedef std::pair<int, int> P;

// 상하좌우
int dr[] = { -1,1, 0,0 };
int dc[] = { 0,0,-1,1 };

// 기본 전역 변수
int N, M, maze[101][101];

// 최단 거리 담을 배열
int dist[101][101];

int main() {
	scanf("%d %d", &M, &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &maze[i][j]);
			dist[i][j] = INF;
		}
	}

	// (0,0)에서 시작 ~ (N-1, M-1)로 도착한다.
	dist[0][0] = 0;
	std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;
	PQ.push(P(0, 0));

	while (!PQ.empty()) {
		// 100으로 나누고, mod를 하는 이유는
		// M,N의 범위가 최대 100이기 때문에 인덱싱을 이렇게 한다.
		// 헷갈렸던 원래 코드

		/*
		int curr_r = PQ.top().second / N;
		int curr_c = PQ.top().second % N;
		=> 이 코드는 N보다 M이 크다면 성립할 것이다.
		=> 그 경우에는 밑에서 PQ에 넣을 때 항상 n_c(< M)가 N보다 작을 것이기 때문에
		=> 위처럼 인덱싱할 때 정확한 값으로 떨어지게 된다.
		=> but, M,N의 대소관계가 나와있지 않을 때, 예를 들어 N < M이라면
		=> n_c(< M)가 N을 초과할 수도 있기 때문에 본래 의도했던 curr_r = v라면 v보다 큰 값이 나올 수 있다.
		*/

		int curr_r = PQ.top().second / 100;
		int curr_c = PQ.top().second % 100;
		PQ.pop();
		//printf("현재 r: %d, c : %d\n", curr_r, curr_c);
		for (int i = 0; i < 4; i++) {
			int n_r = curr_r + dr[i];
			int n_c = curr_c + dc[i];

			if (n_r < 0 || n_r >= N || n_c < 0 || n_c >= M) continue;
			if (dist[n_r][n_c] > dist[curr_r][curr_c] + maze[n_r][n_c]) {
				dist[n_r][n_c] = dist[curr_r][curr_c] + maze[n_r][n_c];
				PQ.push(P(dist[n_r][n_c], (n_r * 100) + n_c));
			}
		}
	}
	
	printf("%d", dist[N - 1][M - 1]);

}