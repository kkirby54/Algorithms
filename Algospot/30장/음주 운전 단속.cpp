#include <cstdio>
#include <vector>
#include <algorithm>

const int INF = 987654321;
using namespace std;
typedef pair<int, int> P;

int V, E, T, A, B, C;
int delay[500];
int dist[500][500];
int W[500][500];

void floyd() {
	// A -> B로 가는데,
	// 그 경로로 가면서 가장 largest인 딜레이를 포함한다.
	// 아니면,
	// i -> 임의의 정점 v.
	// 여기서, v의 drunken을 제외하고,
	// 가는 길에서 가장 컸던 딜레이를 저장한다?

	// Try2. 일단 다 고려해서 돌려.
	// 그 다음에 A,B의 딜레이를 빼면?
	// 어차피 A.B의 딜레이 포함을 해도,
	// 최단거리는 동일하게 나올 것임.
	// => 딜레이는 경로 중 한 번만 포함되는 거라서 안됨.

	// Try3. i -> j로 가는 거 k번째로 딜레이 사용했다면,
	// useDelay[i][j] = k로 저장하자.
	// 그래서 만약에 useDelay[i][j] = k인데, 돌면서,
	// delay[k] > delay[useDelay[i][j]]인 k가 나타나면,
	// delay[useDelay[i][j]]를 빼고,
	// delay[k]를 더한다음에 useDelay[i][j] = k로 업데이트한다.

	// SOL: 그게 아니라,
	// 0, ... K-1 의 정점이 있다고 할 때,
	// 플로이드는 0부터 K-1번 순회하면서 0번 정점을 경유, 1번 정점을 경유, ... 이런 식으로 했음.
	// 그 순서는 그냥 앞에서부터 하면 편하니까 이렇게 한건데,
	// 지금은 그 순서를 "delay가 작은 순"으로 정렬한다.
	// 그러면, delay가 작은 녀석들부터 완화를 시도할 것임.

	vector<P> order;
	for (int i = 0; i < V; i++) order.push_back(P(delay[i], i));
	sort(order.begin(), order.end());

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) W[i][j] = 0;
			else W[i][j] = dist[i][j];
		}
	}

	for (int k = 0; k < V; k++) {
		int w = order[k].second;

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				// w에 따라 달라진다고.
				// W에 들어 가는 거는..
				// 현재 w. 즉 가장 빠른 정점에 대해서
				// 이 딜레이를 포함하고 갔을 때의 최소값을 구한다.
				// 쭉쭉 가다가 w가 마지막, 즉 가장 큰 정점일 때까지 계속되므로
				// 마지막 w에 대해서 고려하면 모든 케이스를 고려한 것임.
				dist[i][j] = min(dist[i][j], dist[i][w] + dist[w][j]);
				W[i][j] = min(W[i][j], dist[i][w] + dist[w][j] + delay[w]);

			}
		}
	}
	
}

int main() {
	scanf("%d %d", &V, &E);
	for (int i = 0; i < V; i++) scanf("%d", delay + i);
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}

	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &A, &B, &C);
		A--; B--;
		dist[A][B] = C;
		dist[B][A] = C;
	}

	floyd();

	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		// A->B로 갈 때 딜레이 포함 최단거리를 구해라.
		scanf("%d %d", &A, &B);
		A--; B--;
		printf("%d\n", W[A][B]);
	}
	
}