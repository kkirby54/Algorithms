#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
const int MAX_N = 100000;


struct RMQ {
	int N;
	vector<int> RangeMin;

	RMQ(const vector<int>& arr) {
		N = arr.size();
		RangeMin.resize(N * 4);
		init(arr, 1, 0, N - 1);
	}

	int init(const vector<int>& arr, int node, int left, int right) {
		if (left == right) return RangeMin[node] = arr[left];

		int mid = (left + right) / 2;
		int leftMin = init(arr, node * 2, left, mid);
		int rightMin = init(arr, node * 2 + 1, mid + 1, right);

		return RangeMin[node] = min(leftMin, rightMin);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 공집합의 경우
		if (nodeRight < left || right < nodeLeft) return INT_MAX;

		// 교집합이 [nodeLeft, nodeRight의 경우]
		if (left <= nodeLeft && nodeRight <= right) return RangeMin[node];

		// 아닌 경우에는 왼, 오 자식을 돈다.
		int mid = (nodeLeft + nodeRight) / 2;
		int leftMin = query(left, right, node * 2, nodeLeft, mid);
		int rightMin = query(left, right, node * 2 + 1, mid + 1, nodeRight);

		return min(leftMin, rightMin);
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, N - 1);
	}
};


int C, N, Q, a, b, v;
vector<int> child[MAX_N];

int no2serial[MAX_N], serial2no[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

// 깊이가 d인 노드 here 이하를 전위 탐색한다.
void traverse(int here, int d, vector<int>& trip) {
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;

	depth[here] = d;

	// trip에 추가해야 한다.
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(no2serial[here]);
	}

}

RMQ* prepareRMQ() {
	nextSerial = 0;
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

// u, v사이의 거리를 구한다. 
int distance(RMQ* rmq, int u, int v) {
	
	// 최소 공통 조상 노드 번호를 찾는다.
	int lu = locInTrip[u];
	int lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);

	int LCA = rmq->query(lu, lv);

	// 그리고 그 번호우
	int parentH = depth[serial2no[LCA]];
	int childH1 = depth[u], childH2 = depth[v];

	return childH1 + childH2 - parentH * 2;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &Q);

		for (int i = 0; i < N; i++) child[i].clear();

		for (int i = 1; i <= N -1; i++) {
			scanf("%d", &v);
			child[v].push_back(i);
		}
		RMQ* rmq = prepareRMQ();
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &a, &b);
			printf("%d\n", distance(rmq, a, b));
		}


	}

}
