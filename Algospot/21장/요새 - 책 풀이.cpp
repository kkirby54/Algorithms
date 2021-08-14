#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int C, N, x[1000], y[1000], r[1000];
struct TreeNode {
	vector<TreeNode*> children;
};

// sqrDist: a번째 원과 b번째 원의 반지름 사이의 거리 제곱 return
__inline int sqr(int x) { return x * x; }
__inline int sqrDist(int a, int b) { return sqr(x[b] - x[a]) + sqr(y[b] - y[a]); }

// a가 b를 포함하면 true.
bool enclose(int a, int b) {
	if (r[a] <= r[b]) return false;
	
	return sqrDist(a, b) < sqr(r[a] - r[b]);
}

// a가 b를 포함하는 최소의 원이어야지,
// a -> b 관계가 성립된다.
bool isChild(int a, int b) {
	if (!enclose(a, b)) return false;

	// i번째 원이
	// a에도 포함되면서, 동시에 b를 포함하면,
	// a-b는 최소로 감싸는 관계가 아니다.
	for (int i = 0; i < N; i++) {
		if (a != i && b != i && enclose(a, i) &&
			enclose(i, b)) return false;
	}
	return true;
}

TreeNode* getTree(int curr) {
	TreeNode* ret = new TreeNode();
	for (int i = 0; i < N; i++) {
		// 직접 포함되면, 자식으로 넣는다.
		if (isChild(curr, i))
			ret->children.push_back(getTree(i));
	}
	return ret;
}
/// 
/// 
/// 
/// 
/// 트리의 지름 찾기
/// 
/// 
/// 
/// 

int longest;

// 이 함수 자체는 curr노드를 루트로 하는 트리의 높이를 구한다.
int getHeight(TreeNode* curr) {
	// 자식들의 높이를 저장할 벡터
	vector<int> heights;

	// 모든 자식을 돌면서 재귀적으로 자식들의 높이를 구한다.
	for (int i = 0; i < curr->children.size(); i++) {
		heights.push_back(getHeight(curr->children[i]));
	}
	sort(heights.begin(), heights.end()); // 정렬한다. (가장 큰 높이를 찾아야 하므로)

	int hSize = heights.size();
	if (!hSize) return 0; // curr노드가 leaf노드인 경우, 높이는 0.

	// 큰 높이를 가지는 상위 2개의 자식노드들의 높이를 더해준 후,
	// 자식 노드1 to curr노드로 오는 길이 1
	// 자식 노드2 to curr노드로 오는 길이 1인 2를 더해줘서 갱신한다.
	if (hSize >= 2) {
		longest = max(longest, heights[hSize - 1] + heights[hSize - 2] + 2); 
	}

	return heights.back() + 1; // 가장 큰 높이에 1을 더한 값이 curr노드의 높이가 된다.
}


int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", x + i, y + i, r + i);
		}
		longest = 0;

		// 0번째가 항상 외벽이다.
		// 0을 루트로 하는 트리를 만든다.
		TreeNode* root = getTree(0);
		int h = getHeight(root);
		printf("%d\n", max(longest, h));
	}

}