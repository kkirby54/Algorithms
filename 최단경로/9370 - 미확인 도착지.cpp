#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

typedef std::pair<int, int> P;
const int INF = 1000000000;

int dist_from_s[2001];
int dist_from_g[2001];
int dist_from_h[2001];

int main() {
	int tc, N, M, T, s, g, h, a, b, d;
	scanf("%d", &tc);

	for (int t = 0; t < tc; t++) {
		scanf("%d %d %d", &N, &M, &T);
		scanf("%d %d %d", &s, &g, &h);
		s--; g--; h--;
		/*
		printf("==================\n");
		printf("N,M,T,s,g,h : %d %d %d %d %d %d", N, M, T, s, g, h);
		printf("==================\n");
		*/

		std::vector<P> adj[2001];
		std::vector<int> ret;
		int goal[101];
		int gh; // gh 사이 거리 저장할 변수
		std::fill(dist_from_s, dist_from_s + 2001, INF);
		std::fill(dist_from_g, dist_from_g + 2001, INF);
		std::fill(dist_from_h, dist_from_h + 2001, INF);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &d);
			a--; b--;
			if ((a == g && b == h) ||
				(a == h && b == g)) gh = d;
			adj[a].push_back(P(b, d));
			adj[b].push_back(P(a, d));
		}

		// t개의 목적지 후보들
		for (int i = 0; i < T; i++)
			scanf("%d", &goal[i]);

		// S에서 시작한다.
		// 1. S에서 모든 곳으로 가는 다익스트라
		std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;
		PQ.push(P(0, s));
		dist_from_s[s] = 0;

		while (!PQ.empty()) {
			int curr = PQ.top().second;
			PQ.pop();

			for (auto& p : adj[curr]) {
				int next = p.first, d = p.second;

				if (dist_from_s[next] > dist_from_s[curr] + d) {
					dist_from_s[next] = dist_from_s[curr] + d;
					PQ.push(P(dist_from_s[next], next));
				}
			}
		}

		// 이 경우에는 무조건,
		// s -> h -> g로 간다.
		// 거기서 g -> 목표지를 골라간다.

		if (dist_from_s[g] > dist_from_s[h]) {

			// g에서 다익
			std::priority_queue<P, std::vector<P>, std::greater<P>> PQ2;
			PQ2.push(P(0, g));
			dist_from_g[g] = 0;

			while (!PQ2.empty()) {
				int curr = PQ2.top().second;
				PQ2.pop();

				for (auto& p : adj[curr]) {
					int next = p.first, d = p.second;

					if (dist_from_g[next] > dist_from_g[curr] + d) {
						dist_from_g[next] = dist_from_g[curr] + d;
						PQ2.push(P(dist_from_g[next], next));
					}
				}
			}

			// 이제 목표지들을 본다.
			for (int index = 0; index < T; index++) {
				int candi = goal[index] - 1;

				if (dist_from_s[candi] ==
					dist_from_s[h] + gh + dist_from_g[candi])
					ret.push_back(candi);
					//printf("얘는 맞네 : %d, 거리 : %d\n", candi + 1, dist_from_s[candi]);
			}

		}
		// s -> g -> h -> 목표
		else {
			// h에서 다익
			std::priority_queue<P, std::vector<P>, std::greater<P>> PQ3;
			PQ3.push(P(0, h));
			dist_from_h[h] = 0;

			while (!PQ3.empty()) {
				int curr = PQ3.top().second;
				PQ3.pop();

				for (auto& p : adj[curr]) {
					int next = p.first, d = p.second;

					if (dist_from_h[next] > dist_from_h[curr] + d) {
						dist_from_h[next] = dist_from_h[curr] + d;
						PQ3.push(P(dist_from_h[next], next));
					}
				}
			}

			// 이제 목표지들을 본다.
			for (int index = 0; index < T; index++) {
				int candi = goal[index] - 1;
					if (dist_from_s[candi] ==
						dist_from_s[g] + gh + dist_from_h[candi])
						ret.push_back(candi);
						//printf("얘는 맞네2 : %d, 거리 : %d\n", candi + 1, dist_from_s[candi]);
			}

		}

		std::sort(ret.begin(), ret.end());
		for (int e : ret) {
			printf("%d ", e + 1);
		}
		puts("");
	}
}