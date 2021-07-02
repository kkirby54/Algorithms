#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

// 1,2,3,4,5,6,7,8이라고 하면
// 그걸 미리 계산해둔다.

int sum = 0;
map<vector<int>, int> toSort;

void memo(int K) {
	//map<vector<int>, int> distance;

	vector<int> perm(K);
	for (int i = 0; i < K; i++) perm[i] = i;

	queue<vector<int>> Q;

	Q.push(perm);
	toSort[perm] = 0;

	// 이제 A를 조작해버리기
	while (!Q.empty()) {
		auto here = Q.front();
		Q.pop();
		//for (auto e : here) printf("%d, ", e);
		//printf("도착, sum = %d\n", sum++);
		auto cost = toSort[here];
		for (int i = 0; i < K; i++) {
			for (int j = i + 2; j <= K; j++) {
				reverse(here.begin() + i, here.begin() + j);
				// 이제 바꿨으니 저장해봐
				if (toSort.count(here) == 0) {
					Q.push(here);
					toSort[here] = cost + 1;
				}

				reverse(here.begin() + i, here.begin() + j);
			}
		}


	}
}


// ********************* 이 함수는 너무 느려서 못 쓴다. 전처리를 해놔야 함. memo() 처럼 ******************
// sorted에서 시작해서,
// 돌린게 perm이 되면 그 횟수를 리턴
int bfs(const vector<int>& perm) {
	int n = perm.size();

	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());

	queue<vector<int>> Q;
	map<vector<int>, int> distance;

	Q.push(perm);
	distance[perm] = 0;

	while (!Q.empty()) {
		auto here = Q.front();
		Q.pop();
		if (here == sorted) return distance[here];

		int cost = distance[here];
		// 가능한 모든 구간을 뒤집는다.
		for (int i = 0; i < n; i++) {
			// (i~j)를 뒤집기.
			// 그니까 perm[i] ~ per[j]까지를 뒤집어
			for (int j = i + 2; j <= n; j++) {
				auto there = here;
				reverse(there.begin() + i, there.begin() + j);

				if (distance.count(there) == 0) {
					Q.push(there);
					distance[there] = cost + 1;	
				}
			}
		}

	}

	return -1;
}
int C, N;

int main() {
	scanf("%d", &C);
	// memo로 다 기록해놔

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		memo(N);
		vector<int> perm(N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &perm[i]);
		}

		vector<int> ret(N);
		// 대소관계로 한번 바꿔보기.
		for (int i = 0; i < N; i++) {
			int rank = 0;
			for (int j = 0; j < N; j++) {
				if (perm[i] > perm[j]) rank++;
			}
			ret[i] = rank;
		}

		printf("%d\n", toSort[ret]);

	}

}