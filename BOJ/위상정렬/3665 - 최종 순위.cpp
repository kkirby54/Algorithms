#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
	int T, N, M, tmp, A, B, curr, rank[500];
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		std::vector<int> adj[500];
		int rank_index[500] = { 0 };
		int indegree[500] = { 0 };

		// rank[i]는 i의 등수를 저장한다.
		for (int i = 0; i < N; i++) {
			scanf("%d", &tmp);
			rank_index[tmp-1] = i;
			rank[i] = tmp-1;
		}

		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &A, &B);

			if (rank_index[A - 1] < rank_index[B - 1]) {
				adj[B - 1].push_back(A - 1);
				indegree[A - 1]++;
			}
			else {
				adj[A - 1].push_back(B - 1);
				indegree[B - 1]++;
			}
		}

		// 이제 O(N2)으로 간선 다 만들기.
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				// 기본적인 틀

				// 근데 상대적인 위치가 바뀐 애들을 찾아서 만약 있다면.
				// TC를 예로 들면 5 4 3 2 1이지만, (2,4) (3,4)는 위치가 바뀌었으므로
				// 이미 2->4, 3->4로 adj에 저장되어 있을 것임. 그런 애들을 만나면 continue.

				if (std::find(adj[rank[j]].begin(), adj[rank[j]].end(),
					rank[i]) != adj[rank[j]].end()) {
					continue;
				}
				else {
					adj[rank[i]].push_back(rank[j]);
					indegree[rank[j]]++;
				}

			}

		}

		std::queue<int> Q;
		std::vector<int> ret;
		bool isPossible = true;
		for (int i = 0; i < N; i++) {
			if (indegree[rank[i]] == 0) Q.push(rank[i]);
		}

		/*
		printf("===================\n");
		for (int i = 0; i < N; i++) {
			printf("%d에 대한 간선 : ", rank[i]);
			for (auto e : adj[rank[i]]) {
				printf("%d ", e);
			}
			printf(" indegree : %d", indegree[rank[i]]);
			puts("");
		}
		printf("===================\n");
		*/

		//printf("답은 : ");
		for (int i = 0; i < N; i++) {
			if (Q.empty()) {
				isPossible = false;
				printf("IMPOSSIBLE\n");
				break;
			}
			if (Q.size() > 1) {
				isPossible = false;
				printf("?\n");
				break;
			}


			curr = Q.front();
			ret.push_back(curr);
			Q.pop();

			for (int e : adj[curr]) {
				if (--indegree[e] == 0) Q.push(e);
			}
		}

		if (isPossible) {
			for (int e : ret) {
				printf("%d ", e + 1);
			}
			puts("");
		}


	}

}