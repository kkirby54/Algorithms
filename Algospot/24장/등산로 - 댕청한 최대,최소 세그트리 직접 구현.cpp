#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Segtree {
	int N;
	vector<int> RangeMax, RangeMin;

	Segtree(const vector<int>& arr) {
		// 원소의 개수
		N = arr.size();
		RangeMax.resize(N * 4);
		RangeMin.resize(N * 4);

		min_init(arr, 0, N - 1, 1);
		max_init(arr, 0, N - 1, 1);
	}

	int min_init(const vector<int>& arr, int left, int right, int node) {
		if (left == right) return RangeMin[node] = arr[left];

		int mid = (left + right) / 2;
		int leftMin = min_init(arr, left, mid, node * 2);
		int rightMin = min_init(arr, mid + 1, right, node * 2 + 1);

		return RangeMin[node] = min(leftMin, rightMin);
	}
	int max_init(const vector<int>& arr, int left, int right, int node) {
		if (left == right) return RangeMax[node] = arr[left];

		int mid = (left + right) / 2;
		int leftMax = max_init(arr, left, mid, node * 2);
		int rightMax = max_init(arr, mid + 1, right, node * 2 + 1);

		return RangeMax[node] = max(leftMax, rightMax);
	}

	int query_min(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 교집합 없는 경우
		if (nodeRight < left || right < nodeLeft) return INT_MAX;
		
		// nodeLeft-nodeRight가 쏙 포함되는 경우
		// 이미 우리가 init 함수에서 해놧으니까 바로 리턴
		if (left <= nodeLeft && nodeRight <= right) return RangeMin[node];

		// 그 외의 경우는 걍 재귀
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query_min(left, right, node * 2, nodeLeft, mid),
			query_min(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int query_max(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 교집합 없는 경우
		if (nodeRight < left || right < nodeLeft) return 0;

		// nodeLeft-nodeRight가 쏙 포함되는 경우
		// 이미 우리가 init 함수에서 해놧으니까 바로 리턴
		if (left <= nodeLeft && nodeRight <= right) return RangeMax[node];

		// 그 외의 경우는 걍 재귀
		int mid = (nodeLeft + nodeRight) / 2;
		return max(query_max(left, right, node * 2, nodeLeft, mid),
			query_max(left, right, node * 2 + 1, mid + 1, nodeRight));

	}

};

int C, N, Q, a, b;

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &Q);

		vector<int> Arr(N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &Arr[i]);
		}

		Segtree tree(Arr);
		// 이제 여기서 min 처리, max 처리 완료된 Segtree가 존재한다.
		// 그러면 쿼리에 대한 처리를 하려면.
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &a, &b);
			// 이 쿼리에 답한다.
			int ret = 
			tree.query_max(a, b, 1, 0, tree.N - 1)-tree.query_min(a, b, 1, 0, tree.N - 1);
			printf("%d\n", ret);
		}

	}


}


